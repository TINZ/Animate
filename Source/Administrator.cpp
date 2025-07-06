//	Filename:		Adminitrator.cpp
//	Version:		Final
//	Author:			Paul Tinsley (pmbtin)
//	Date:			26 February, 1999
//	Platform:		Visual C++ 5.00

//	Purpose:		See Administrator.h.

#include "stdafx.h"
#include "Administrator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	*** CONSTRUCTOR ***

Administrator::Administrator()	:ad_agents(NULL), ad_env(40), ad_arb(),
								 ad_script_pos(0), ads_type(0), ads_name(0),
								 ads_x(0), ads_y(0), ads_action(0), ads_quantity(0),
								 ads_target_x(0), ads_target_y(0), ad_dim(40)

{

	ad_agents.clear();
	ad_intents.clear();
	ad_script.clear();
	ad_last_script.clear();

}

//	*** DESTRUCTOR ***

Administrator::~Administrator()

{

	deallocate_agents();
	ad_agents.clear();
	ad_intents.clear();
	ad_script.clear();
	ad_last_script.clear();

}
	
//	*** PUBLIC FUNCTIONS ***

bool Administrator::setup_miner1(const bool explore, const short miners,
								 const short miner_r, const short grab,
								 const short sack, const short grid_size,
								 ifstream &m)

{

	if(miners <= 0)

	{

		ofstream err("errlog.txt", ios::app);
		err << "ERROR, Administrator::setup_miner1(args), there must be\n";
		err << "at least one miner agent. Setup failed.\n";
		err.close();
		return(false);

	}

	// metamorphose environment to correct size
	ad_env.metamorphose(grid_size);
	
	// get the environment dimension
	ad_dim = grid_size;
	
	// input the environment map
	ad_env.input_objects(m);

	// check environment state
	if(!ad_env.get_state())

	{

		ofstream err("errlog.txt", ios::app);
		err << "ERROR, Administrator::setup_miner1(args), map file stream was\n";
		err << "not freshly opened, or the data file was invalid. Unable to\n";
		err << "setup this scenario.\n";
		err.close();
		return(false);

	}

	PATH temp;
	triple alloc;
	short x,y;
	bool starts_exist = false;
	
	// check for user defined ASTART positions

	if(ad_env.contains_object(ASTART))

	{

		starts_exist = true;

		for(x = 0 ; x < ad_dim ; x++)

		{

			for(y = 0 ; y < ad_dim ; y++)

			{
							
				if(ad_env.get_object_f(x,y) == ASTART)

				{

					alloc.put(x,y,1);
					temp.push_back(alloc);
					
				}

			}

		}

		// are there enough start positions?

		if(temp.size() < miners)

		{

			// add all SPACE too

			for(x = 0 ; x < ad_dim ; x++)

			{

				for(y = 0 ; y < ad_dim ; y++)

				{
								
					if(ad_env.get_object(x,y) == SPACE)

					{

						alloc.put(x,y,0);
						temp.push_back(alloc);
						
					}

				}

			}

		}

		// erase ASTART markers
		ad_env.clear_objects(ASTART);
			
	}

	else

	{

		// build a list of available locations to place agents
		for(x = 0 ; x < ad_dim ; x++)

		{

			for(y = 0 ; y < ad_dim ; y++)

			{
							
				if(ad_env.get_object(x,y) == SPACE)

				{

					alloc.put(x,y,0);
					temp.push_back(alloc);
					
				}

			}

		}

	}

	// de-allocate agents from the heap
	deallocate_agents();

	// erase agents
	ad_agents.clear();

	// erase intents
	ad_intents.clear();

	// erase animation scripts
	ad_script.clear();
	ad_last_script.clear();

	// setup arbitrator fail value
	ad_arb.set_fail(NOTHING);

	// check that enough space for agents
	if(temp.size() < miners)

	{

		ofstream err("errlog.txt", ios::app);
		err << "ERROR, Administrator::setup_miner1(args), there was not\n";
		err << "enough space in the environment to place all of the agents.\n";
		err << "Scenario setup failed.\n";
		err.close();
		return(false);
	
	}
	
	// seed random number generator
	srand( (unsigned)time( NULL ) );
	
	// place agents randomly within available space
	short i;					// loop counter
	short ax;					// generic coordinate variable
	short ay;					// generic coordinate variable
	PATH_IT loc = temp.begin();	// to manipulate available spaces to place agents
	short place;				// to find a place
	short max;					// loop limit
	
	// Agent names must run sequentially with vector index from
	// zero to (number of agents)-1
	
	short junk;	// because we are using class triple and dont need third argument
	Miner *mr;	// pointer to a Miner
	
	// create Miners
	
	for(i = 0 ; i < miners ; i++)

	{

		if(starts_exist)

		{

			loc = temp.begin();
			loc -> get(ax,ay,junk);
			
			// if we have hit a space, stop fixed alloc
			if(junk == 0)

			{

				starts_exist = false;
				max = temp.size();			// get size of available space
				place = rand() % max;		// do random selection
				loc = temp.begin() + place;	// find place
				loc -> get(ax,ay,junk);		// get coordinates
				temp.erase(loc,loc+1);		// erase this place - can't be used again

			}

			else

			{

				temp.erase(loc,loc+1);

			}
						
		}

		else

		{

			// place agents randomly over available space
			max = temp.size();			// get size of available space
			place = rand() % max;		// do random selection
			loc = temp.begin() + place;	// find place
			loc -> get(ax,ay,junk);		// get coordinates
			temp.erase(loc,loc+1);		// erase this place - can't be used again

		}
				
		mr =  new Miner(ad_dim,0,0,&ad_env,0,miner_r,sack,grab);
		mr -> init(i,ax,ay,MINER);	// set name and start coords
		mr -> record_position();		// make agent record its position
		
		if(!explore)					// if agents not exploring

		{

			mr -> get_environment();	// load map into memory

		}

		ad_agents.push_back(mr);		// make this agent
				
	}

	// tidy up expensive memory!
	ad_intents.resize(miners);
	ad_agents.resize(miners);
	
	// do initial intents - should all be NOTHING
	get_intentions();

	//	copy initial intents to arbitrator
	ad_arb.set_initial_intents(ad_intents);

	// set script position - used in script construction
	ad_script_pos = 0;

	// generate initial turn in scripts
	update_script();

	return(true);

}

bool Administrator::setup_miner2(const bool explore, const short miners,
								 const short miner_r, const short grab,
								 const short sack, const short grid_size,
								 ifstream &m)

{

	if(miners <= 0)

	{

		ofstream err("errlog.txt", ios::app);
		err << "ERROR, Administrator::setup_miner2(args), there must be\n";
		err << "at least one miner agent. Setup failed.\n";
		err.close();
		return(false);

	}

	// metamorphose environment to correct size
	ad_env.metamorphose(grid_size);
	
	// get environment dimension
	ad_dim = grid_size;
	
	// input the environment map
	ad_env.input_objects(m);

	// check environment state
	if(!ad_env.get_state())

	{

		ofstream err("errlog.txt", ios::app);
		err << "ERROR, Administrator::setup_miner2(args), map file stream was\n";
		err << "not freshly opened, or the data file was invalid. Unable to\n";
		err << "setup this scenario.\n";
		err.close();
		return(false);

	}
		
	PATH temp;
	triple alloc;
	short x,y;
	bool starts_exist = false;
	
	// check for user defined ASTART positions

	if(ad_env.contains_object(ASTART))

	{

		starts_exist = true;

		for(x = 0 ; x < ad_dim ; x++)

		{

			for(y = 0 ; y < ad_dim ; y++)

			{
							
				if(ad_env.get_object_f(x,y) == ASTART)

				{

					alloc.put(x,y,1);
					temp.push_back(alloc);
					
				}

			}

		}

		// are there enough start positions?

		if(temp.size() < miners)

		{

			// add all SPACE too

			for(x = 0 ; x < ad_dim ; x++)

			{

				for(y = 0 ; y < ad_dim ; y++)

				{
								
					if(ad_env.get_object(x,y) == SPACE)

					{

						alloc.put(x,y,0);
						temp.push_back(alloc);
						
					}

				}

			}

		}

		// erase ASTART markers
		ad_env.clear_objects(ASTART);
			
	}

	else

	{

		// build a list of available locations to place agents
		for(x = 0 ; x < ad_dim ; x++)

		{

			for(y = 0 ; y < ad_dim ; y++)

			{
							
				if(ad_env.get_object(x,y) == SPACE)

				{

					alloc.put(x,y,0);
					temp.push_back(alloc);
					
				}

			}

		}

	}

	// de-allocate agents from the heap
	deallocate_agents();

	// erase agents
	ad_agents.clear();

	// erase intents
	ad_intents.clear();

	// erase animation scripts
	ad_script.clear();
	ad_last_script.clear();

	// setup arbitrator fail value
	ad_arb.set_fail(NOTHING);

	// check that enough space for agents
	if(temp.size() < miners)

	{

		ofstream err("errlog.txt", ios::app);
		err << "ERROR, Administrator::setup_miner2(args), there was not\n";
		err << "enough space in the environment to place all of the agents.\n";
		err << "Scenario setup failed.\n";
		err.close();
		return(false);
		
	}
	
	// seed random number generator
	srand( (unsigned)time( NULL ) );
	
	// place agents randomly within available space
	short i;					// loop counter
	short ax;					// generic coordinate variable
	short ay;					// generic coordinate variable
	PATH_IT loc = temp.begin();	// to manipulate available spaces to place agents
	short place;				// to find a place
	short max;					// loop limit
	
	// Agent names must run sequentially with vector index from
	// zero to (number of agents)-1
	
	short junk;	// because we are using class triple and dont need third argument
	ChainMiner *mr;	// pointer to a Miner
	
	// create ChainMiners
	for(i = 0 ; i < miners ; i++)

	{

		if(starts_exist)

		{

			loc = temp.begin();
			loc -> get(ax,ay,junk);
			
			// if we have hit a space, stop fixed alloc
			if(junk == 0)

			{

				starts_exist = false;
				max = temp.size();			// get size of available space
				place = rand() % max;		// do random selection
				loc = temp.begin() + place;	// find place
				loc -> get(ax,ay,junk);		// get coordinates
				temp.erase(loc,loc+1);		// erase this place - can't be used again

			}

			else

			{

				temp.erase(loc,loc+1);

			}
						
		}

		else

		{

			// place agents randomly over available space
			max = temp.size();			// get size of available space
			place = rand() % max;		// do random selection
			loc = temp.begin() + place;	// find place
			loc -> get(ax,ay,junk);		// get coordinates
			temp.erase(loc,loc+1);		// erase this place - can't be used again

		}
		
		mr =  new ChainMiner(ad_dim, 0, 0, &ad_env, 0, miner_r, sack, grab);
		mr -> init(i, ax, ay, MINER);	// set name and start coords
		mr -> record_position();		// make agent record its position
		
		if(!explore)					// agents not exploring

		{

			mr -> get_environment();	// load map into memory

		}

		ad_agents.push_back(mr);		// make this agent
				
	}
		
	// tidy up memory
	ad_intents.resize(miners);
	ad_agents.resize(miners);
	
	// do initial intents - should all be NOTHING
	get_intentions();

	//	copy initial intents to arbitrator
	ad_arb.set_initial_intents(ad_intents);

	// record script position
	ad_script_pos = 0;

	// generate initial turn in scripts
	update_script();

	return(true);

}

bool Administrator::setup_hunting(const bool explore, const short predators,
								  const short prey, const short predator_r,
								  const short prey_r, const short stom,
								  const short stom_max, const short grid_size,
								  ifstream &m)

{

	if(predators <= 0 || prey <= 0)

	{

		ofstream err("errlog.txt", ios::app);
		err << "ERROR, Administrator::setup_hunting(args), there must be\n";
		err << "at least one agent per category. Setup failed.\n";
		err.close();
		return(false);

	}

	// metamorphose environment to correct size
	ad_env.metamorphose(grid_size);

	// get environment dimension
	ad_dim = grid_size;
	
	// input the environment map
	ad_env.input_objects(m);

	// check state of environment
	if(!ad_env.get_state())

	{

		ofstream err("errlog.txt", ios::app);
		err << "ERROR, Administrator::setup_hunting(args), map file stream was\n";
		err << "not freshly opened, or the data file was invalid. Unable to\n";
		err << "setup this scenario.\n";
		err.close();
		return(false);

	}

	PATH temp;
	triple alloc;
	short x,y;
	bool starts_exist = false;
	
	// check for user defined ASTART positions

	if(ad_env.contains_object(ASTART))

	{

		starts_exist = true;

		for(x = 0 ; x < ad_dim ; x++)

		{

			for(y = 0 ; y < ad_dim ; y++)

			{
							
				if(ad_env.get_object_f(x,y) == ASTART)

				{

					alloc.put(x,y,1);
					temp.push_back(alloc);
					
				}

			}

		}

		// are there enough start positions?

		if(temp.size() < (predators + prey))

		{

			// add all SPACE too

			for(x = 0 ; x < ad_dim ; x++)

			{

				for(y = 0 ; y < ad_dim ; y++)

				{
								
					if(ad_env.get_object(x,y) == SPACE)

					{

						alloc.put(x,y,0);
						temp.push_back(alloc);
						
					}

				}

			}

		}

		// erase ASTART markers
		ad_env.clear_objects(ASTART);
			
	}

	else

	{

		// build a list of available locations to place agents
		for(x = 0 ; x < ad_dim ; x++)

		{

			for(y = 0 ; y < ad_dim ; y++)

			{
							
				if(ad_env.get_object(x,y) == SPACE)

				{

					alloc.put(x,y,0);
					temp.push_back(alloc);
					
				}

			}

		}

	}

	// de-allocate agents from the heap
	deallocate_agents();

	// erase agents
	ad_agents.clear();

	// erase intents
	ad_intents.clear();
	
	// erase animation scripts
	ad_script.clear();
	ad_last_script.clear();

	// setup arbitrator fail value
	ad_arb.set_fail(NOTHING);

	// check that enough space for agents
	if(temp.size() < (predators + prey))

	{

		ofstream err("errlog.txt", ios::app);
		err << "ERROR, Administrator::setup_hunting(args), there was not\n";
		err << "enough space in the environment to place all of the agents.\n";
		err << "Scenario setup failed.\n";
		err.close();
		return(false);
		
	}
	
	// seed random number generator
	srand( (unsigned)time( NULL ) );
	
	// place agents randomly within available space
	short i;					// loop counter
	short ax;					// generic coordinate variable
	short ay;					// generic coordinate variable
	PATH_IT loc = temp.begin();	// to manipulate available spaces to place agents
	short place;				// to find a place
	short max;					// loop limit
	short name;					// to maintain correct agent naming
	
	// Agent names must run sequentially with vector index from
	// zero to (number of agents)-1
	
	short junk;	// because we are using class triple and dont need third argument

	Predator *pred;	// pointer to a Predator
	Prey *pry;		// pointer to a Prey
	
	// create Predators
	for(i = 0 ; i < predators ; i++)

	{

		if(starts_exist)

		{

			loc = temp.begin();
			loc -> get(ax,ay,junk);
			
			// if we have hit a space, stop fixed alloc
			if(junk == 0)

			{

				starts_exist = false;
				max = temp.size();			// get size of available space
				place = rand() % max;		// do random selection
				loc = temp.begin() + place;	// find place
				loc -> get(ax,ay,junk);		// get coordinates
				temp.erase(loc,loc+1);		// erase this place - can't be used again

			}

			else

			{

				temp.erase(loc,loc+1);

			}
						
		}

		else

		{

			// place agents randomly over available space
			max = temp.size();			// get size of available space
			place = rand() % max;		// do random selection
			loc = temp.begin() + place;	// find place
			loc -> get(ax,ay,junk);		// get coordinates
			temp.erase(loc,loc+1);		// erase this place - can't be used again

		}
		
		pred =  new Predator(ad_dim, 0, 0, &ad_env, 0, predator_r, stom, stom_max);
		pred -> init(i, ax, ay, PREDATOR);	// set name and start coords
		pred -> record_position();			// make agent record its position
		
		if(!explore)						// if agents not exploring

		{

			pred -> get_environment();		// load map into memory

		}

		ad_agents.push_back(pred);			// make this agent
				
	}

	name = i;	// must keep names contiguous

	// create Prey
	for(i = name ; i < (predators + prey) ; i++)

	{

		if(starts_exist)

		{

			loc = temp.begin();
			loc -> get(ax,ay,junk);
			
			// if we have hit a space, stop fixed alloc
			if(junk == 0)

			{

				starts_exist = false;
				max = temp.size();			// get size of available space
				place = rand() % max;		// do random selection
				loc = temp.begin() + place;	// find place
				loc -> get(ax,ay,junk);		// get coordinates
				temp.erase(loc,loc+1);		// erase this place - can't be used again

			}

			else

			{

				temp.erase(loc,loc+1);

			}
						
		}

		else

		{

			// place agents randomly over available space
			max = temp.size();			// get size of available space
			place = rand() % max;		// do random selection
			loc = temp.begin() + place;	// find place
			loc -> get(ax,ay,junk);		// get coordinates
			temp.erase(loc,loc+1);		// erase this place - can't be used again

		}
		
		pry =  new Prey(ad_dim, 0, 0, &ad_env, 0, prey_r);
		pry -> init(i, ax, ay, PREY);	// set name and start coords
		pry -> record_position();		// make agent record its position
		
		if(!explore)					// if not exploring

		{

			pry -> get_environment();	// load map into memory

		}

		ad_agents.push_back(pry);		// make this agent
				
	}

	// tidy up memory
	ad_intents.resize((predators + prey));
	ad_agents.resize((predators + prey));
	
	// do initial intents - should all be NOTHING
	get_intentions();

	//	copy initial intents to arbitrator
	ad_arb.set_initial_intents(ad_intents);

	// set script position
	ad_script_pos = 0;

	// generate initial turn in scripts
	update_script();

	return(true);

}

bool Administrator::setup_crowd1(const bool explore,const short crowders,const short crowder_r,
						const short grid_size,ifstream &m)

{

	if(crowders <= 0)

	{

		ofstream err("errlog.txt", ios::app);
		err << "ERROR, Administrator::setup_crowd1(args), there must be\n";
		err << "at least one crowd agent. Setup failed.\n";
		err.close();
		return(false);

	}

	// metamorphose environment to correct size
	ad_env.metamorphose(grid_size);
	
	// get the environment dimension
	ad_dim = grid_size;
	
	// input the environment map
	ad_env.input_objects(m);

	// check environment state
	if(!ad_env.get_state())

	{

		ofstream err("errlog.txt", ios::app);
		err << "ERROR, Administrator::setup_crowd1(args), map file stream was\n";
		err << "not freshly opened, or the data file was invalid. Unable to\n";
		err << "setup this scenario.\n";
		err.close();
		return(false);

	}

	PATH temp;
	triple alloc;
	short x,y;
	bool starts_exist = false;
	
	// check for user defined ASTART positions

	if(ad_env.contains_object(ASTART))

	{

		starts_exist = true;

		for(x = 0 ; x < ad_dim ; x++)

		{

			for(y = 0 ; y < ad_dim ; y++)

			{
							
				if(ad_env.get_object_f(x,y) == ASTART)

				{

					alloc.put(x,y,1);
					temp.push_back(alloc);
					
				}

			}

		}

		// are there enough start positions?

		if(temp.size() < crowders)

		{

			// add all SPACE too

			for(x = 0 ; x < ad_dim ; x++)

			{

				for(y = 0 ; y < ad_dim ; y++)

				{
								
					if(ad_env.get_object(x,y) == SPACE)

					{

						alloc.put(x,y,0);
						temp.push_back(alloc);
						
					}

				}

			}

		}

		// erase ASTART markers
		ad_env.clear_objects(ASTART);
			
	}

	else

	{

		// build a list of available locations to place agents
		for(x = 0 ; x < ad_dim ; x++)

		{

			for(y = 0 ; y < ad_dim ; y++)

			{
							
				if(ad_env.get_object(x,y) == SPACE)

				{

					alloc.put(x,y,0);
					temp.push_back(alloc);
					
				}

			}

		}

	}

	// de-allocate agents from the heap
	deallocate_agents();

	// erase agents
	ad_agents.clear();

	// erase intents
	ad_intents.clear();

	// erase animation scripts
	ad_script.clear();
	ad_last_script.clear();

	// setup arbitrator fail value
	ad_arb.set_fail(NOTHING);

	// check that enough space for agents
	if(temp.size() < crowders)

	{

		ofstream err("errlog.txt", ios::app);
		err << "ERROR, Administrator::setup_crowd1(args), there was not\n";
		err << "enough space in the environment to place all of the agents.\n";
		err << "Scenario setup failed.\n";
		err.close();
		return(false);
	
	}
	
	// seed random number generator
	srand( (unsigned)time( NULL ) );
	
	// place agents randomly within available space
	short i;					// loop counter
	short ax;					// generic coordinate variable
	short ay;					// generic coordinate variable
	PATH_IT loc = temp.begin();	// to manipulate available spaces to place agents
	short place;				// to find a place
	short max;					// loop limit
	
	// Agent names must run sequentially with vector index from
	// zero to (number of agents)-1
	
	short junk;	// because we are using class triple and dont need third argument
	Crowd *cr;	// pointer to a Crowd agent
	
	// create Crowd agents
	
	for(i = 0 ; i < crowders ; i++)

	{

		if(starts_exist)

		{

			loc = temp.begin();
			loc -> get(ax,ay,junk);
			
			// if we have hit a space, stop fixed alloc
			if(junk == 0)

			{

				starts_exist = false;
				max = temp.size();			// get size of available space
				place = rand() % max;		// do random selection
				loc = temp.begin() + place;	// find place
				loc -> get(ax,ay,junk);		// get coordinates
				temp.erase(loc,loc+1);		// erase this place - can't be used again

			}

			else

			{

				temp.erase(loc,loc+1);

			}
						
		}

		else

		{

			// place agents randomly over available space
			max = temp.size();			// get size of available space
			place = rand() % max;		// do random selection
			loc = temp.begin() + place;	// find place
			loc -> get(ax,ay,junk);		// get coordinates
			temp.erase(loc,loc+1);		// erase this place - can't be used again

		}
				
		cr =  new Crowd(ad_dim,0,0,&ad_env,0,crowder_r);
		cr -> init(i,ax,ay,MINER);	// set name and start coords
		cr -> record_position();		// make agent record its position
		
		if(!explore)					// if agents not exploring

		{

			cr -> get_environment();	// load map into memory

		}

		ad_agents.push_back(cr);		// make this agent
				
	}

	// tidy up expensive memory!
	ad_intents.resize(crowders);
	ad_agents.resize(crowders);
	
	// do initial intents - should all be NOTHING
	get_intentions();

	//	copy initial intents to arbitrator
	ad_arb.set_initial_intents(ad_intents);

	// set script position - used in script construction
	ad_script_pos = 0;

	// generate initial turn in scripts
	update_script();

	return(true);

}

void Administrator::update_script()

{

	// first update non-agent objects
	
	// erase copy of last turn
	ad_last_script.clear();

	chunk data(0,0,0,0,0,0,0,0,0);
	short count = 0;
	
	// set an info field
	ad_script.push_back(data);
	ad_last_script.push_back(data);
	
	// get non-agent object states
	for(ads_x = 0 ; ads_x < ad_dim ; ads_x++)

	{

		for(ads_y = 0 ; ads_y < ad_dim ; ads_y++)

		{

			ad_env.get_object_f(ads_x,ads_y,ads_type,ads_quantity);
			
			// only want objects that are not obstacles,space or agents
			if(ads_type >= MINERAL)
				
			{	// ads_type, ads_name, ads_x, ads_y, ads_action,
				// ads_quantity, ads_target_x, ads_target_y

				data.put(0,ads_type,0,ads_x,ads_y,0,ads_quantity,0,0);
				// alter coords for last script
				data.screen_coords();
				ad_script.push_back(data);
				ad_last_script.push_back(data);
				count++;

			}

		}

	}
	
	// now get agents
	AGENTS_IT iter;
	
	// ads_type, ads_name, ads_x, ads_y, ads_action,
	// ads_quantity, ads_target_x, ads_target_y

	for(iter = ad_agents.begin() ; iter != ad_agents.end() ; ++iter)

	{

		(*iter) -> get_state(ads_type, ads_name, ads_x, ads_y, ads_action,
								ads_quantity,ads_target_x, ads_target_y);
		
		if(ads_type != SPACE)	// agents died and been eaten up or rotted away

		{
			
			data.put(0,ads_type,ads_name,ads_x,ads_y,ads_action,ads_quantity,
						ads_target_x,ads_target_y);
			//adjust coords for anim
			data.screen_coords();
			ad_script.push_back(data);
			ad_last_script.push_back(data);
			count++;

		}

	}

	// now record total objects in info fields
	data.put(1,count,0,0,0,0,0,0,0);
	ad_script[ad_script_pos] = data;
	ad_last_script[0] = data;
	ad_script_pos += ((long)count+1);

}

void Administrator::deliberate()

{

	// allow agents to ponder
	AGENTS_IT i;

	for(i = ad_agents.begin() ; i != ad_agents.end() ; ++i)

	{

		(*i) -> think();

	}

}

void Administrator::get_intentions()

{

	AGENTS_IT a_i;
	
	ad_intents.clear();

	for(a_i = ad_agents.begin() ; a_i != ad_agents.end() ; ++a_i)

	{

		ad_intents.push_back((*a_i) -> get_intent());

	}

}

void Administrator::set_intentions()

{

	INTENT_LIST_IT i_i;
	
	for(i_i = ad_intents.begin() ; i_i != ad_intents.end() ; ++i_i)

	{

		ad_agents[i_i -> get_name()] -> put_intent(*i_i);

	}

}

void Administrator::execute_actions()

{

	AGENTS_IT a;
	
	for(a = ad_agents.begin() ; a != ad_agents.end() ; ++a)

	{

		(*a) -> execute_action();
	
	}
	
}

void Administrator::arbitrate()

{

	ad_arb.arbitrate(ad_intents);

}

void Administrator::get_script(SCRIPT &s)

{

	s = ad_script;

}

void Administrator::get_last_turn(SCRIPT &s)

{

	s = ad_last_script;

}

void Administrator::check_hunting_POUNCE()

{

	// walk the intents and look for action POUNCE

	INTENT_LIST_IT i_i;
	triple t;
	PATH p;
	short x,y,z,c,x1,y1;
	
	for(i_i = ad_intents.begin() ; i_i != ad_intents.end() ; ++i_i)

	{

		if(i_i -> get_action() == POUNCE)

		{

			i_i -> get(x,y);
			t.put(x,y,0);
			p.push_back(t);	// build a list of locations where a POUNCE took place

		}

	}

	if(!p.size())

	{

		//nothing further to do
		return;

	}

	//look for all agents whose coords match those in p and kill them

	AGENTS_IT a;
	short agent_name = -1;
	
	for(a = ad_agents.begin() ; a != ad_agents.end() ; ++a)

	{

		agent_name++;

		(*a) -> get_location(x1,y1);
		
		for(c = 0 ; c < p.size() ; c++)

		{

			p[c].get(x,y,z);
		
			if(x==x1 && y==y1)

			{

				// do chance to see if pounce successful
				if((rand() % 100) > 59)

				{
					
					(*a) -> kill();
					// adjust intention
					ad_intents[agent_name].set_action(NOTHING);
					
				}

			}

		}
		
	}

}

void Administrator::deallocate_agents()

{

	if(ad_agents.size())

	{

		AGENTS_IT i;

		for(i = ad_agents.begin() ; i != ad_agents.end() ; ++i)

		{

			delete(*i);

		}

	}

}