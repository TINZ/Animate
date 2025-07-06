//	Filename:		Agent.cpp
//	Version:		1.0
//	Author:			Paul Tinsley (pmbtin)
//	Date:			11 January, 1999
//	Platform:		Visual C++ 5.00 Console Application, release build

//	Purpose:		Base class of agents. See Agent.h

#include "stdafx.h"
#include "Agent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	*** CONSTRUCTORS ***

Agent::Agent(const short s, const short x, const short y, Environment *e,
			 const short n, const short r, const short t): ag_x(x), ag_y(y),
			 ag_env(e), ag_m(s), ag_s(s), ag_name(n), ag_v_range(r),
			 ag_type(t), ag_alive(true), ag_orig_type(t), ag_dim(s),
			 ag_search_prep(false)
		
{
	
	// initialise memory to unknown
	ag_m.wipe(UNKNOWN);
	
	// allocate and resize search list
	ag_search.reserve((s*s)+s);
	ag_search.resize((s*s)+s);
	
	if(!(ag_env -> check_coord(ag_x, ag_y)))

	{
		
		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Agent::Agent(s,x,y,*e,n,r,t), Agent\n";
		err << ag_name << " has been placed at an invalid location.\n";
		err << "FORCED EXIT!\n";
		err.close();
		exit(1);

	}
	
	// set initial intent
	ag_intent.put(n,NOTHING,0,x,y,s);

	// erase targetting
	erase_target();

}

Agent::Agent(const Agent &a)

{

	ag_m = a.ag_m;					// Agent's memory
	ag_s = a.ag_s;					// search memory
	ag_x = a.ag_x;					// current x-coordinate
	ag_y = a.ag_y;					// current y_coordinate
	ag_target_x = a.ag_target_x;	// Agent's target x
	ag_target_y = a.ag_target_y;	// Agent's target y
	ag_env = a.ag_env;				// Agent's environment
	ag_name = a.ag_name;			// Agent's name
	ag_v_range = a.ag_v_range;		// Agent's vision range
	ag_intent = a.ag_intent;		// Agent's next intended action
	ag_type = a.ag_type;			// Agent's type
	ag_orig_type = a.ag_orig_type;	// copy of type
	ag_alive = a.ag_alive;			// alive or dead
	ag_target = a.ag_target;		// whether an object is targetted by Agent
	ag_target_obj = a.ag_target_obj;// the object targetted
	ag_dim = a.ag_dim;				// memory & environment dimension
	ag_search = a.ag_search;		// search list
	ag_search_prep = a.ag_search_prep;	// whether total search done at ag_x,ag_y
		
}

//	*** OPERATORS ***

Agent & Agent::operator =(const Agent &a)

{

	ag_m = a.ag_m;					
	ag_s = a.ag_s;
	ag_x = a.ag_x;
	ag_y = a.ag_y;
	ag_target_x = a.ag_target_x;
	ag_target_y = a.ag_target_y;
	ag_env = a.ag_env;
	ag_name = a.ag_name;
	ag_v_range = a.ag_v_range;
	ag_intent = a.ag_intent;
	ag_type = a.ag_type;
	ag_orig_type = a.ag_orig_type;
	ag_alive = a.ag_alive;
	ag_target = a.ag_target;
	ag_target_obj = a.ag_target_obj;
	ag_dim = a.ag_dim;
	ag_search = a.ag_search;
	ag_search_prep = a.ag_search_prep;
		
	return(*this);
		
}

//	*** PUBLIC FUNCTION PROTOTYPES

void Agent::record_position()

{
		
	// check position according to [ag_x] and [ag_y]

	if(ag_env -> get_object(ag_x, ag_y) != SPACE)

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Agent::record_position(), Agent has been placed at a\n";
		err << "location that does not contain SPACE.\nFORCED EXIT!\n";
		err.close();
		exit(1);

	}

	// record position and set intention to NOTHING

	ag_intent.put(ag_name,NOTHING,0,ag_x,ag_y,ag_dim);
	ag_m.put(ag_x,ag_y,ag_type);
	ag_env -> put_object(ag_x,ag_y,ag_type,1);
		
}

void Agent::get_intent(Intent &i)

{

	i = ag_intent;

}

void Agent::put_intent(Intent i)

{

	ag_intent = i;

}

Intent Agent::get_intent()

{

	return(ag_intent);

}

void Agent::init(const short n, const short x, const short y, const short t)

{

	ag_name = n;
	ag_x = x;
	ag_y = y;
	ag_type = t;
	ag_intent.put(ag_name,NOTHING,0,ag_x,ag_y,ag_dim);
	ag_dim = ag_m.get_dim();
	
}

void Agent::init(const short x, const short y)

{

	ag_x = x;
	ag_y = y;
	ag_intent.put(NOTHING,ag_x,ag_y);
	ag_dim = ag_m.get_dim();
	
}

void Agent::get_location(short &x, short &y)

{

	x = ag_x;
	y = ag_y;

}

void Agent::kill()

{

	ag_alive = false;
	ag_type = CARCASS;
	// make a 200 point value carcass
	ag_env -> put_object_f(ag_x,ag_y,ag_type,200);

}

const bool Agent::is_alive()

{

	return(ag_alive);

}

const short Agent::get_name()

{

	return(ag_name);

}

const short Agent::get_type()

{

	return(ag_type);

}

const short Agent::get_original_type()

{

	return(ag_orig_type);

}

void Agent::get_state(short &t, short &n, short &x, short &y, short &a, short &q,
					  short &tx, short &ty)

{

	t = ag_type;
	n = ag_name;
	x = ag_x;
	y = ag_y;
	a = ag_intent.get_action();
	q = 0;

	if(ag_target)

	{

		tx = ag_target_x;
		ty = ag_target_y;

	}

	else

	{

		tx = -1;
		ty = -1;

	}

}

void Agent::get_environment()

{

	ag_env -> get_all_objects(ag_m);

}

//	** BEHAVIOURS AND ABILITIES **

void Agent::look()

{
	
	short lim = ag_v_range*2;
	short x = ag_x - ag_v_range;
	short y = ag_y - ag_v_range;
	short c1,c2,cx,cy;
		
	for(c1 = 0; c1 <= lim ; c1++)

	{

		for(c2 = 0 ; c2 <= lim ; c2++)

		{

			cx = x + c1;
			cy = y + c2;

			if(ag_m.check(cx,cy)) // is this a valid position

			{

				ag_m.put_f(cx,cy,ag_env -> get_object_f(cx,cy));
			
			}

		}

	}

	// sort out targets that have gone
	if(ag_target)

	{

		if(ag_target_x >= x && ag_target_x <= x + lim &&
			ag_target_y >= y && ag_target_y <= y + lim)

		{

			if(ag_m.get_f(ag_target_x,ag_target_y) != ag_target_obj)

			{

				erase_target();

			}

		}

	}
	
}

void Agent::set_target(const short x, const short y, const short o)

{
	
	ag_target_x = x;
	ag_target_y = y;
	ag_target = true;
	ag_target_obj = o;

}

void Agent::erase_target()

{
	
	ag_target_x = -1;
	ag_target_y = -1;
	ag_target = false;
	ag_target_obj = -1;

}

bool Agent::seek_target(const short x, const short y, const short o)

{
		
	// if already adjacent to target, not worth seeking it

	if(adjacent_to(x,y))

	{

		erase_target();
		return(false);

	}

	// world is dynamic - so we should search at each iteration
	
	update_search_memory();
	
	// need to flood search grid
	
	execute_partial_search_flood(x,y);

	// search grid no longer ready for testing closest objects
	ag_search_prep = false;

	// if no value in [ag_s] at agent's location then target is
	// not reachable at present

	if(ag_s.get_f(ag_x,ag_y) == 0)

	{

		return(false);
				
	}

	short c1,c2,cx,cy;	// indices on [moves[args]]
	short gox = 0;		// a best x-coord
	short goy = 0;		// a best y-coord
	short score,temp;	// getting lowest cost score
	bool hit = false;	// whether a move is possible
	
	score = MAX_VALUE;	// we need a high value to compare against
						// values in the search grid

	// get lowest score position in search grid that is adjacent
	// to the agent

	for(c1 = 0 ; c1 < (MOVE_DIM - 1) ; c1+=2)

	{

		c2 = c1 + 1;

		cx = ag_x + moves[c1];
		cy = ag_y + moves[c2];

		if(ag_s.check(cx,cy))
	
		{
			
			
			temp = ag_s.get_f(cx,cy);
			//temp < score && temp != -1 && temp != 0)
			if(temp < score && temp > 0)

			{
				
				// record this move
				score = temp;
				gox = cx;
				goy = cy;
				hit = true;
				
			}
				
		}

	}

	// check that we got a move

	if(hit)

	{
		
		// record agent's intended action
		set_target(x,y,o);
		ag_intent.put(MOVE,gox,goy);
		return(true);
				
	}
	
	// no moves possible at present
	return(false);
	
}

bool Agent::targetting()

{

	return(ag_target);

}

void Agent::execute_move()

{
		
	short a,x,y;
	ag_intent.get(a,x,y);	// retrive the action
	short region = ag_env -> get_object_f(x,y);
	
	if(a != MOVE)

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Agent::execute_move(), this function can only handle\n";
		err << "actions that are type MOVE.\n";
		err << "Action has FAILED.\n";
		err.close();
		return;

	}

	if(region != SPACE)

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Agent::execute_move(), Agent " << ag_name << " has been allowed to\n";
		err << "move to a blocked region located at (" << x << "," << y << ")\n";
		err << "This region contains identifier " << region << "\n";
		err << "Action has FAILED.\n";
		err << "Agent's coordinates are: " << ag_x << "," << ag_y << "\n";
		err.close();
		return;

	}

	ag_env -> put_object_f(ag_x,ag_y,SPACE,0);		// remove Agent's presence
	ag_m.put_f(ag_x,ag_y,SPACE);					// update memory
	ag_x = x;										// set new position
	ag_y = y;
	ag_env -> put_object_f(ag_x,ag_y,ag_type,1);	// record new location
	ag_m.put_f(ag_x,ag_y,ag_type);					// update memory
	
}

void Agent::do_nothing()

{
	
	ag_intent.put(NOTHING,ag_x,ag_y);
	ag_target = false;

}

void Agent::expire_moving_objects()

{

	ag_m.expire_moving();

}

bool Agent::wander(short &x, short &y)

{

	PATH p;
	triple t;
	short z,choice;

	if(!ag_search_prep)

	{

		update_search_memory();
		execute_search_flood(ag_x,ag_y);
		ag_search_prep = true;

	}

	// build a list of space, guarantee it can be reached
	
	// note that UNKNOWN areas in [ag_m] have priority recorded in [z]
	for(x = 0 ; x < ag_dim ; x++)

	{

		for(y = 0 ; y < ag_dim ; y++)

		{

			if((z = ag_s.get_f(x,y)) > 0 && !(ag_x == x && ag_y == y)) // i can reach it

			{

				if(!next_to(x,y,UNKNOWN))

				{

					// make path cost huge
					z = MAX_VALUE;

				}
				
				t.put(x,y,z);
				p.push_back(t);

			}

		}

	}

	if(!p.size())

	{

		// no places to get to!!
		return(false);

	}
		
	// sort into lowest path cost first
	// triple defined as sorted by third tuplet
	sort(p.begin(),p.end());

	// get first value
	p[0].get(x,y,z);

	// if no unknowns
	if(z == MAX_VALUE)

	{

		// take a random place
		choice = rand() % p.size();
		p[choice].get(x,y,z);
		return(true);

	}

	return(true);
	
}

bool Agent::adjacent_to(const short o)

{

	short c1,c2,cx,cy;

	for(c1 = 0 ; c1 < (MOVE_DIM - 1) ; c1+=2)

	{

		c2 = c1 + 1;

		cx = ag_x + moves[c1];
		cy = ag_y + moves[c2];

		if(ag_m.check(cx,cy))

		{

			if(ag_m.get_f(cx,cy) == o)

			{

				return(true);

			}

		}

	}

	return(false);

}

bool Agent::adjacent_to(const short x, const short y)

{

	short c1,c2,cx,cy;

	for(c1 = 0 ; c1 < (MOVE_DIM - 1) ; c1+=2)

	{

		c2 = c1 + 1;
		
		cx = ag_x + moves[c1];
		cy = ag_y + moves[c2];

		if(ag_m.check(cx,cy))

		{

			if((cx == x) && (cy == y))

			{

				return(true);

			}

		}

	}

	return(false);

}

bool Agent::adjacent_to(short &x, short &y, const short o)

{

	short c1,c2,cx,cy;

	for(c1 = 0 ; c1 < (MOVE_DIM - 1) ; c1+=2)

	{

		c2 = c1 + 1;

		cx = ag_x + moves[c1];
		cy = ag_y + moves[c2];

		if(ag_m.check(cx,cy))

		{

			if(ag_m.get_f(cx,cy) == o)

			{

				x = cx;
				y = cy;
				return(true);

			}

		}

	}

	return(false);

}

bool Agent::knows_of(const short o)

{

	return(ag_m.find_instance(o));
	
}

bool Agent::knows_of_closest(short &x, short &y, const short o)

{

	// flood at agent's coordinates
	
	if(!ag_search_prep)

	{

		update_search_memory();
		execute_search_flood(ag_x,ag_y);
		ag_search_prep = true;

	}

	short x1,y1,c1,c2,cx,cy,temp;
	short path_cost = MAX_VALUE;
	bool hit = false;
	
	// look for accessible objects

	for(x1 = 0 ; x1 < ag_dim ; x1++)

	{

		for(y1 = 0 ; y1 < ag_dim ; y1++)

		{
			
			if(ag_m.get_f(x1,y1) == o)

			{
				
				// look at adjacent

				for(c1 = 0 ; c1 < (MOVE_DIM - 1) ; c1+=2)

				{

					c2 = c1 + 1;

					cx = x1 + moves[c1];
					cy = y1 + moves[c2];

					if(ag_s.check(cx,cy))

					{

						temp = ag_s.get_f(cx,cy);

						// if closer and accessible
						if(temp < path_cost && temp > 0)

						{
							
							path_cost = temp;
							x = x1;
							y = y1;
							hit = true;
							
						}

					}

				}

			}

		}

	}
	
	return(hit);

}

//	*** PROTECTED FUNCTIONS ***

void Agent::update_search_memory()

{
		
	ag_s = ag_m;

	ag_s.replace_all_non_zero_instances(-1);

	ag_s.put_f(ag_x,ag_y,0);

	ag_search_prep = false;
		
}

void Agent::execute_search_flood(short x, short y)

{

	short value = 10;			// path costs
	short c1,c2;				// allowable move counters							
	short cx,cy;				// relative positioning			
	short put_value;			// paths costs
	short temp;					// value comparison
	short count = 0;			// loop counter
	bool hypotenuse = true;		// a toggle that represents a diagonal move
	triple t(x,y,value);		// for recording algorithm progress
	ag_search.clear();			// clear the search list
	ag_search.push_back(t);		// set first value
	ag_s.put_f(x,y,value);		// record first value in search grid
	
	// whilst we are not at the end of search list
	while(count < ag_search.size())

	{

		// get this value
		ag_search[count].get(x,y,value);
		
		// look at neighbours
		for(c1 = 0 ; c1 < (MOVE_DIM - 1) ; c1+=2)

		{

			c2 = c1 + 1;
			cx = x + moves[c1];			// make new position
			cy = y + moves[c2];			// make new position
			hypotenuse = !hypotenuse;	// toggle hypotenuse
			
			// if this coordinate is valid
			if(ag_s.check(cx,cy))
				
			{
				
				// if this coordinate is not blocked
				if((temp = ag_s.get_f(cx,cy)) != -1)

				{

					put_value = value;	// make path value
							
					// if diagonal transition
					if(hypotenuse)

					{
						
						// note lazy evaluation so order of statements
						// is crucial due to assign and test
						// if new path cost < this value or a space
						if(((put_value += 14) < temp) || temp == SPACE)

						{
						
							// record new value and push onto back of list
							ag_s.put_f(cx,cy,put_value);
							t.put(cx,cy,put_value);
							ag_search.push_back(t);

						}
						
					}

					else

					{

						if(((put_value += 10) < temp) || temp == SPACE)

						{

							ag_s.put_f(cx,cy,put_value);
							t.put(cx,cy,put_value);
							ag_search.push_back(t);

						}
						
					}

				}

			}

		}

		count++;
		
	};

}

void Agent::execute_partial_search_flood(short x, short y)

{

	short value = 10;			// path costs
	short c1,c2;				// allowable move counters							
	short cx,cy;				// relative positioning			
	short put_value;			// paths costs
	short temp;					// value comparison
	short count = 0;			// loop counter
	bool hypotenuse = true;		// a toggle that represents a diagonal move
	triple t(x,y,value);		// for recording algorithm progress
	ag_search.clear();			// clear the search list
	ag_search.push_back(t);		// set first value
	ag_s.put_f(x,y,value);		// record first value in search grid
	
	// whilst we are not at the end of search list
	while(count < ag_search.size())

	{

		// get this value
		ag_search[count].get(x,y,value);

		// finish if at Agent's location
		if(ag_x == x && ag_y == y)

		{

			return;

		}
		
		// look at neighbours
		for(c1 = 0 ; c1 < (MOVE_DIM - 1) ; c1+=2)

		{

			c2 = c1 + 1;
			cx = x + moves[c1];			// make new position
			cy = y + moves[c2];			// make new position
			hypotenuse = !hypotenuse;	// toggle hypotenuse
			
			// if this coordinate is valid
			if(ag_s.check(cx,cy))
				
			{
				
				// if this coordinate is not blocked
				if((temp = ag_s.get_f(cx,cy)) != -1)

				{

					put_value = value;	// make path value
							
					// if diagonal transition
					if(hypotenuse)

					{
						
						// if new path cost < this value or a space
						if(((put_value += 14) < temp) || temp == SPACE)

						{
						
							// record new value and push onto back of list
							ag_s.put_f(cx,cy,put_value);
							t.put(cx,cy,put_value);
							ag_search.push_back(t);

						}
						
					}

					else

					{

						if(((put_value += 10) < temp) || temp == SPACE)

						{

							ag_s.put_f(cx,cy,put_value);
							t.put(cx,cy,put_value);
							ag_search.push_back(t);

						}
						
					}

				}

			}

		}

		count++;
		
	};

}

bool Agent::next_to(const short x, const short y, const short o)

{

	short c1,c2,cx,cy;

	for(c1 = 0 ; c1 < (MOVE_DIM - 1) ; c1+=2)

	{

		c2 = c1 + 1;

		cx = x+moves[c1];
		cy = y+moves[c2];

		if(ag_m.check(cx,cy))

		{

			if(ag_m.get_f(cx,cy) == o)

			{

				return(true);

			}

		}

	}

	return(false);

}

/*

  void Agent::expire_moving_objects()

{

	short region;

	for(short x = 0 ; x < ag_dim ; x++)

	{

		for(short y = 0 ; y < ag_dim ; y++)

		{

			//remove all MOVING things except self
			region = ag_m.get_f(x,y);

			// needs a defintion of what a moving thing is really
			if(region >= MINER && region < MINERAL && !(ag_x == x && ag_y == y))
				
			{

				ag_m.put_f(x,y,SPACE);

			}

		}

	}

}

*/