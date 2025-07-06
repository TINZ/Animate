//	Filename:		Predator.cpp
//	Version:		Final
//	Author:			Paul Tinsley (pmbtin)
//	Date:			26 February, 1999
//	Platform:		Visual C++ 5.00

//	Purpose:		See Predator.h

//	Refer to Agent.h for details of some functions.

#include "stdafx.h"
#include "Predator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	*** OPERATORS ***

Predator & Predator::operator =(const Predator &a)

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

	// Predator privates

	p_stomach = a.p_stomach;			// stomach contents
	p_stomach_max = a.p_stomach_max;	// max stomach contents

	return(*this);
		
}

//	*** PUBLIC FUNCTIONS **

void Predator::get_state(short &t, short &n, short &x, short &y, short &a, short &q,
							short &tx, short &ty)

{
	
	t = ag_type;
	n = ag_name;
	x = ag_x;
	y = ag_y;
	a = ag_intent.get_action();
	q = p_stomach;

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

void Predator::think()

{

	Agent::think();

	short x, y;

	// GET RID OF ALL OTHER MOVING TARGETS

	expire_moving_objects();
		
	// OBSERVE THE ENVIRONMENT

	look();

	// FEED

	if(hungry() && (adjacent_to(x,y,CARCASS)))

	{

		feed(x,y);
		return;

	}

	// POUNCE

	if(hungry() && (adjacent_to(x,y,PREY)))

	{

		pounce(x,y);
		return;

	}

	if(hungry() && knows_of(CARCASS))

	{

		if(knows_of_closest(x,y,CARCASS))

		{

			if(seek_target(x,y,CARCASS))

			{

				return;

			}

		}

	}

	if(hungry() && knows_of(PREY))

	{

		if(knows_of_closest(x,y,PREY))

		{
		
			if(seek_target(x,y,PREY))

			{

				return;

			}

		}

	}

	if(targetting())

	{

		if(seek_target(ag_target_x,ag_target_y,ag_target_obj))

		{

			return;

		}

	}

	if(!wander(x,y))

	{

		do_nothing();

	}

	else if(!seek_target(x,y,SPACE))

	{

		do_nothing();

	}
		
}

void Predator::pounce(const short x, const short y)

{

	if((adjacent_to(x,y)) && (ag_env -> get_object(x,y) == PREY))

	{

		ag_intent.put(POUNCE,x,y);
		erase_target();

	}

	else

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Predator::pounce(x,y), Illogical\n";
		err << "location to pounce on. Prey does not exist at this location.\n";
		err << "Action has failed and agent will do nothing!\n";
		err.close();
		do_nothing();

	}

}

void Predator::feed(const short x, const short y)

{

	if((adjacent_to(x,y)) && (ag_env -> get_object(x,y) == CARCASS))

	{

		ag_intent.put(GRAB,x,y);
		erase_target();

	}

	else

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Predator::feed(x,y), Illogical\n";
		err << "location to feed from. Carcass does not exist at this location.\n";
		err << "Action has failed and agent will do nothing!\n";
		err.close();
		do_nothing();

	}

}

void Predator::execute_feed(const short x, const short y)

{
	
	short object, quantity, bite, bitten;

	ag_env -> get_object(x,y,object,quantity);

	if(object == CARCASS && quantity > 0)

	{

		bite = p_stomach_max - p_stomach;

		if(bite > 10)

		{
			bite = 10;

		}
		
		bitten = ag_env -> take_quantity_f(x,y,bite);

		p_stomach += bitten;

	}

}

void Predator::execute_action()

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

				execute_feed(x,y);
				break;

			case POUNCE:

				break;
			
			default:

				ofstream err("errlog.txt", ios::app);
				err << "\n\nERROR, Predator::execute_action(), Predator " << ag_name << endl;
				err << "attempting to perform illogical action. Action failed!\n";
				err.close();
				break;
					
		}

	}
	
}

const bool Predator::hungry()

{

	return(!(p_stomach == p_stomach_max));

}