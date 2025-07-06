//	Filename:		Miner.cpp
//	Version:		Final
//	Author:			Paul Tinsley (pmbtin)
//	Date:			26 February, 1999
//	Platform:		Visual C++ 5.00

//	Purpose:		See Miner.h. Derived from base class Agent.h.

//	Refer to Agent.h for details of some functions.

#include "stdafx.h"
#include "Miner.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	*** OPERATORS ***

Miner & Miner::operator =(const Miner &a)

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

	// Miner privates

	m_sack = a.m_sack;			// a sack for carrying things
	m_sack_max = a.m_sack_max;	// max capacity of sack
	m_scoop = a.m_scoop;		// max amount Miner can scoop in one turn
	
	return(*this);
		
}

//	*** PUBLIC FUNCTIONS **

void Miner::get_state(short &t, short &n, short &x, short &y, short &a, short &q,
						short &tx, short &ty)

{
	
	t = ag_type;				// type
	n = ag_name;				// name
	x = ag_x;					// current x-coord
	y = ag_y;					// current y-coord
	a = ag_intent.get_action();	// current action
	q = m_sack;					// sack contents

	if(ag_target)

	{

		tx = ag_target_x;		// target x-coord
		ty = ag_target_y;		// target y-coord

	}

	else

	{

		tx = -1;
		ty = -1;

	}

}

void Miner::think()

{

	Agent::think();

	short x,y;
	
	// REMOVE ALL MOBILE THINGS FROM MEMORY

	expire_moving_objects();
		
	// OBSERVE THE ENVIRONMENT

	look();
	
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
	
	// if not already seeking minerals and knows of minerals and sack isn't full
	if(ag_target_obj != MINERAL && !sack_full() && knows_of(MINERAL))

	{
		
		// if knows of a mineral and is nearest
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

	// not targeting a home base and has some minerals but does not know of any more
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

		// stop an do nothing
		do_nothing();

	}

	else

	{

		// if can get there
		if(seek_target(x,y,SPACE))
				
		{
	
			// then end this turn
			return;

		}

		else

		{

			// stop and do nothing
			do_nothing();

		}
				
	}
		
}

const bool Miner::sack_full()

{

	return(m_sack == m_sack_max);

}

void Miner::mine_minerals(const short x, const short y)

{

	if(sack_full())

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Miner::mine_minerals(x, y), Miner\n";
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
			err << "\n\nERROR, Miner::mine_minerals(x, y), Either\n";
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
		err << "\n\nERROR, Miner::mine_minerals(x, y), Invalid\n";
		err << "coordinates. Action has failed and Miner will do\n";
		err << "nothing!\n";
		err.close();
		do_nothing();

	}

}

void Miner::empty_backpack(const short x, const short y)

{

	if(sack_empty())

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Miner::empty_backpack(x, y), Miners\n";
		err << "backpack is empty.Action has failed and Miner\n";
		err << "will do nothing!\n";
		err.close();
		do_nothing();
		return;

	}
	
	if(ag_m.check(x,y))

	{
	
		if(ag_m.get_f(x,y) == HOME && adjacent_to(x,y))

		{

			ag_intent.put(DROP,x,y);
			// stop any targetting
			erase_target();

		}

		else

		{

			ofstream err("errlog.txt", ios::app);
			err << "\n\nERROR, Miner::empty_backpack(x, y), Illogical\n";
			err << "location to drop ORE. Action has failed and Miner\n";
			err << "will do nothing!\n";
			err.close();
			do_nothing();

		}

	}

	else

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Miner::empty_backpack(x, y), Invalid\n";
		err << "coordinates. Action has failed and Miner will do\n";
		err << "nothing!\n";
		err.close();
		do_nothing();

	}

}

const bool Miner::sack_empty()

{

	return(!m_sack);

}

const short Miner::sack_space()

{

	return(m_sack_max - m_sack);

}

void Miner::execute_mine_minerals(const short x, const short y)

{
	
	short object,quantity,grab,grabbed;

	// check that minerals exist
	ag_env -> get_object(x,y,object,quantity);

	if(object == MINERAL && quantity > 0)

	{

		grab = sack_space();

		if(grab >= m_scoop)

		{

			grab = m_scoop;

		}

		// get minerals
		grabbed = ag_env -> take_quantity_f(x,y,grab);
		m_sack += grabbed;

	}

}

void Miner::execute_empty_backpack(const short x, const short y)

{
		
	if(ag_env -> get_object_f(x,y) == HOME)

	{

		if(ag_env -> add_quantity_f(x,y,ORE,m_sack))
		
		{
			
			m_sack = 0;

		}

		else

		{

			ofstream err("errlog.txt", ios::app);
			err << "\n\nCAUTION, Miner::execute_empty_backpack(x,y), There\n";
			err << "was not enough space to drop the objects.\n";
			err << "Action has failed!\n";
			err.close();

		}
		
	}

	else

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Miner::execute_empty_backpack(x,y), Miner\n";
		err << "dropping ore on a location other than HOME.\n";
		err << "Action has failed!\n";
		err.close();

	}
	
}

void Miner::execute_action()

{
		
	if(ag_alive)

	{

		short a,x,y;
		ag_intent.get(a,x,y);
	
		switch(a)

		{

			case NOTHING:

				break;

			case MOVE:

				execute_move();
				break;

			case GRAB:

				execute_mine_minerals(x,y);
				break;

			case DROP:

				execute_empty_backpack(x,y);
				break;
			
			default:

				ofstream err("errlog.txt", ios::app);
				err << "\n\nERROR, Miner::execute_action(), Miner " << ag_name << endl;
				err << "attempting to perform illogical action. Action failed!\n";
				err.close();
				break;
					
		}

	}
	
}