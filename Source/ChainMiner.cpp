//	Filename:		ChainMiner.cpp
//	Version:		Final
//	Author:			Paul Tinsley (pmbtin)
//	Date:			26 February, 1999
//	Platform:		Visual C++ 5.00 Console Application, release build

//	Purpose:		See ChainMiner.h

//	Refer to Agent.h for details of some functions.

#include "stdafx.h"
#include "ChainMiner.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	*** OPERATORS ***

ChainMiner & ChainMiner::operator =(const ChainMiner &a)

{

	// base class privates
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

	// ChainMiner privates

	cm_sack = a.cm_sack;				// a sack for carrying things
	cm_sack_max = a.cm_sack_max;		// max capacity of sack
	cm_scoop = a.cm_scoop;				// max amount Miner can scoop in one turn
	cm_endurance = a.cm_endurance;		// getting tired
	cm_facing = a.cm_facing;			// heading

	return(*this);
		
}

//	*** PUBLIC FUNCTIONS **

void ChainMiner::get_state(short &t, short &n, short &x, short &y, short &a, short &q,
						short &tx, short &ty)

{
	
	t = ag_type;
	n = ag_name;
	x = ag_x;
	y = ag_y;
	a = ag_intent.get_action();
	q = cm_sack;

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

void ChainMiner::think()

{

	Agent::think();

	short x,y;
	
	// REMOVE ALL MOBILE THINGS FROM MEMORY

	expire_moving_objects();
		
	// OBSERVE THE ENVIRONMENT

	look();

	// HANDLE TIRING

	if(tired())

	{

		if(!sack_empty())

		{
			
			// deposit at home base
			if(adjacent_to(x,y,HOME))

			{

				empty_backpack(x,y);
				return;

			}

			// deposit on existing ore
			if(adjacent_to(x,y,ORE))

			{

				empty_backpack(x,y);
				return;

			}

			// deposit on a space, facing preferred
			if(facing_is_space(x,y))

			{

				empty_backpack(x,y);
				return;

			}
		
			do_nothing();
			erase_target();
			return;

		}

		do_nothing();
		erase_target();
		return;
		
	}

	// if not recovered and sack empty
	if(!recovered() && sack_empty())

	{

		do_nothing();
		return;

	}

	// DROPPING MINERALS AT A HOME BASE

	// if next to a home and has some minerals
	if(!sack_empty() && adjacent_to(x,y,HOME))

	{
		
		// then deposit minerals and finish this turn
		empty_backpack(x,y);
		return;

	}

	// MINING MINERALS
	
	// if next to minerals and sack isn't full
	if(!sack_full() && adjacent_to(x,y,MINERAL))

	{
		
		// then mine minerals and end this turn
		mine_minerals(x,y);
		return;

	}

	// LOCATING AND HEADING TOWARDS MINERALS
	
	// if knows of minerals and sack isn't full and not targeting minerals
	if(ag_target_obj != MINERAL && !sack_full() && knows_of(MINERAL))

	{
		
		// if can get to closest
		if(knows_of_closest(x,y,MINERAL))

		{
						
			// if can get to minerals
			if(seek_target(x,y,MINERAL))
				
			{
			
				// then end this turn
				return;

			}
		
		}
						
	}
	
	// FINDING A HOME BASE TO DEPOSIT MINERALS

	// if sack is full and not already targetting a home base
	if(ag_target_obj != HOME && sack_full())

	{

		// if knows of a home base and is nearest
		if(knows_of_closest(x,y,HOME))

		{

			// if can get to home base
			if(seek_target(x,y,HOME))

			{

				// then end this turn
				return;

			}
	
		}

	}
	
	// RETURNING TO A HOME BASE - NO MORE MINERALS TO MINE

	// if has some minerals but does not know of any more and not targeting minerals
	if(ag_target_obj != HOME && !sack_empty() && !knows_of(MINERAL))

	{

		// if knows of a closest home base
		if(knows_of_closest(x,y,HOME))

		{
		
			// if can get to home base
			if(seek_target(x,y,HOME))

			{

				// then end this turn
				return;

			}
			
		}

	}
	
	// GRABBING ORE
	
	// if next to ore and sack isn't full and recovered
	if(!sack_full() && recovered() && adjacent_to(x,y,ORE))

	{
		
		// then mine ore and end this turn
		grab_ore(x,y);
		return;

	}

	// LOCATING AND HEADING TOWARDS ORE
	
	// if knows of ore and sack isn't full and not targeting ore and not knows
	// of any minerals
	if(recovered() && ag_target_obj != ORE && !sack_full() &&
		knows_of(ORE) && !knows_of(MINERAL))

	{
		
		// if can get to closest
		if(knows_of_closest(x,y,ORE))

		{
						
			// if can get to ore
			if(seek_target(x,y,ORE))
				
			{
			
				// then end this turn
				return;

			}
		
		}
						
	}
	
	// CONTINUING TARGETTING

	// if targetting anything
	if(targetting())

	{
		
		// if can get to it
		if(seek_target(ag_target_x,ag_target_y,ag_target_obj))
				
		{

			// then end this turn
			return;

		}
		
	}
	
	// STARTING WANDERING

	// if nowhere to wander to
	if(!wander(x,y))

	{

		do_nothing();

	}

	else

	{

		if(seek_target(x,y,SPACE))
				
		{
	
			// then end this turn
			return;

		}

		else

		{

			do_nothing();

		}
				
	}

}

const bool ChainMiner::sack_full()

{

	return(cm_sack == cm_sack_max);

}

void ChainMiner::mine_minerals(const short x, const short y)

{

	if(sack_full())

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, ChainMiner::mine_minerals(x, y), Miner\n";
		err << "wants to mine minerals but his backpack is full.\n";
		err << "Action has failed and Miner will do nothing!\n";
		err.close();
		do_nothing();
		return;

	}
	
	if(ag_m.check(x,y))

	{
			
		if(ag_m.get_f(x,y) == MINERAL && adjacent_to(x,y))

		{

			ag_intent.put(GRAB,x,y);
			// stop any targetting
			erase_target();

		}

		else

		{

			ofstream err("errlog.txt", ios::app);
			err << "\n\nERROR, ChainMiner::mine_minerals(x, y), Either\n";
			err << "minerals do not exist or Miner is not adjacent\n";
			err << "to any minerals. Action has failed and Miner\n";
			err << "will do nothing!\n";
			err.close();
			do_nothing();

		}


	}

	else

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, ChainMiner::mine_minerals(x, y), Invalid\n";
		err << "coordinates. Action has failed and Miner will do\n";
		err << "nothing!\n";
		err.close();
		do_nothing();

	}

}

void ChainMiner::grab_ore(const short x, const short y)

{

	if(sack_full())

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, ChainMiner::grab_ore(x, y), Miner\n";
		err << "wants to pick up ORE but his backpack is full.\n";
		err << "Action has failed and Miner will do nothing!\n";
		err.close();
		do_nothing();
		return;

	}
	
	if(ag_m.check(x,y))

	{
	
		if(ag_m.get_f(x,y) == ORE && adjacent_to(x,y))

		{

			ag_intent.put(GRAB, x, y);
			// stop any targetting
			erase_target();

		}

		else

		{

			ofstream err("errlog.txt", ios::app);
			err << "\n\nERROR, ChainMiner::grab_ore(x, y), Either\n";
			err << "ORE does not exist or Miner is not adjacent\n";
			err << "to any ORE. Action has failed and Miner\n";
			err << "will do nothing!\n";
			err.close();
			do_nothing();

		}


	}

	else

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, ChainMiner::grab_ore(x, y), Invalid\n";
		err << "coordinates. Action has failed and Miner will do\n";
		err << "nothing!\n";
		err.close();
		do_nothing();

	}

}

void ChainMiner::empty_backpack(const short x, const short y)

{

	if(sack_empty())

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, ChainMiner::empty_backpack(x, y), Miners\n";
		err << "backpack is empty.Action has failed and Miner\n";
		err << "will do nothing!\n";
		err.close();
		do_nothing();
		return;

	}
	
	if(ag_m.check(x,y))

	{

		short region = ag_m.get_f(x,y);
	
		if((region == HOME || region == ORE || region == SPACE) && adjacent_to(x,y))

		{

			ag_intent.put(DROP,x,y);
			// stop any targetting
			erase_target();

		}
		
		else

		{

			ofstream err("errlog.txt", ios::app);
			err << "\n\nERROR, ChainMiner::empty_backpack(x, y), Illogical\n";
			err << "location to drop ORE. Action has failed and Miner\n";
			err << "will do nothing!\n";
			err.close();
			do_nothing();

		}


	}

	else

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, ChainMiner::empty_backpack(x, y), Invalid\n";
		err << "coordinates. Action has failed and Miner will do\n";
		err << "nothing!\n";
		err.close();
		do_nothing();

	}

}

const bool ChainMiner::sack_empty()

{

	return(cm_sack == 0);

}

const short ChainMiner::sack_space()

{

	return(cm_sack_max - cm_sack);

}

void ChainMiner::execute_mine_minerals(const short x, const short y)

{
	
	short object, quantity, grab, grabbed;

	ag_env -> get_object(x, y, object, quantity);

	if(object == MINERAL && quantity > 0)

	{

		grab = sack_space();

		if(grab >= cm_scoop)

		{

			grab = cm_scoop;

		}

		grabbed = ag_env -> take_quantity_f(x,y,grab);

		cm_sack += grabbed;

	}

}

void ChainMiner::execute_grab_ore(const short x, const short y)

{
	
	short object, quantity, grab, grabbed;

	ag_env -> get_object(x, y, object, quantity);

	if(object == ORE && quantity > 0)

	{

		grab = sack_space();	// can pick up sack_space if no mining effort
		
		grabbed = ag_env -> take_quantity_f(x,y,grab);

		cm_sack += grabbed;

	}

}

void ChainMiner::execute_empty_backpack(const short x, const short y)

{
	
	short object = ag_env -> get_object_f(x,y);

	if((object == HOME || object == ORE || object == SPACE))

	{

		if(ag_env -> add_quantity_f(x,y,ORE,cm_sack))
		
		{
			
			cm_sack = 0;

		}

		else

		{

			ofstream err("errlog.txt", ios::app);
			err << "\n\nCAUTION, ChainMiner::execute_empty_backpack(x, y), There\n";
			err << "was not enough space to drop the objects.\n";
			err << "Action has failed!\n";
			err.close();

		}
		
	}

	else

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, ChainMiner::execute_empty_backpack(x, y), Miner\n";
		err << "attempted to drop cargo at invalid region.\n";
		err << "Action has failed!\n";
		err.close();

	}
		
}

void ChainMiner::execute_action()

{
		
	if(ag_alive)

	{

		short a, x, y;
		ag_intent.get(a,x,y);
		set_facing(x,y);
		
		switch(a)

		{

			case NOTHING:

				recover();
				break;

			case MOVE:
				
				execute_move();
				
				if(!sack_empty())

				{

					tire();

				}

				else

				{

					recover();

				}

				break;

			case GRAB:

				if(ag_env -> get_object(x,y) == MINERAL)

				{
					
					execute_mine_minerals(x, y);
					recover();

				}

				else if(ag_env -> get_object(x,y) == ORE)

				{

					execute_grab_ore(x, y);

				}

				break;

			case DROP:

				execute_empty_backpack(x,y);
				break;
			
			default:

				ofstream err("errlog.txt", ios::app);
				err << "\n\nERROR, ChainMiner::execute_action(), Miner " << ag_name << endl;
				err << "attempting to perform illogical action. Action failed!\n";
				err.close();
				break;
					
		}

	}
	
}

const bool ChainMiner::tired()

{

	return(cm_endurance <= 0);

}

const bool ChainMiner::recovered()

{

	return(cm_endurance == 12);

}

void ChainMiner::tire()

{

	cm_endurance--;

	if(cm_endurance < 0)

	{

		cm_endurance = 0;

	}

}

void ChainMiner::recover()

{

	cm_endurance++;

	if(cm_endurance > 12)

	{

		cm_endurance = 12;

	}

}

void ChainMiner::set_facing(const short x, const short y)

{

	short c1,c2;

	for(c1 = 0 ; c1 < (MOVE_DIM - 1) ; c1+=2)

	{

		c2 = c1 + 1;
		
		// get index of this heading over moves[]
		if((x == ag_x + moves[c1]) && (y == ag_y + moves[c2]))
			
		{

			cm_facing = c1;
			break;

		}

	}
		
}

const bool ChainMiner::facing_is_space(short &x, short &y)

{
	
	x = ag_x + moves[cm_facing];
	y = ag_y + moves[cm_facing+1];

	// if facing location is space - select it
	if(ag_m.check(x,y))

	{

		if(ag_m.get_f(x,y) == SPACE)

		{

			return(true);

		}
		
	}

	else

	{

		// count spaces around agent and select by random
		short c1,c2,cx,cy;
		PATH p;
		triple t;

		for(c1 = 0 ; c1 < (MOVE_DIM - 1) ; c1+=2)

		{

			c2 = c1 + 1;
			cx = ag_x + moves[c1];
			cy = ag_y + moves[c2];

			// get list of spaces
			if(ag_m.check(cx,cy))

			{

				if(ag_m.get_f(cx,cy) == SPACE)

				{

					t.put(cx,cy,0);
					p.push_back(t);

				}

			}
			
		}

		if(p.size())

		{

			c1 = rand() % p.size();
			p[c1].get(x,y,c2);
			return(true);

		}

	}

	return(false);	
	
}