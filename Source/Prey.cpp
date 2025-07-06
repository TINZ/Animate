//	Filename:		Prey.cpp
//	Version:		Final
//	Author:			Paul Tinsley (pmbtin)
//	Date:			26 February, 1999
//	Platform:		Visual C++ 5.00

//	Purpose:		See Prey.h

//	Refer to Agent.h for details of some functions.

#include "stdafx.h"
#include "Prey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	*** PUBLIC FUNCTIONS **

void Prey::get_state(short &t, short &n, short &x, short &y, short &a, short &q,
						short &tx, short &ty)

{
	
	t = ag_type;
	n = ag_name;
	x = ag_x;
	y = ag_y;
	a = ag_intent.get_action();
	q = ag_env -> get_quantity_f(ag_x,ag_y);

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

void Prey::think()

{

	Agent::think();

	short x,y;

	// HANDLE DEATH

	// if dead
	if(!is_alive())

	{
		
		// if not converted to a SPACE
		if(ag_type != SPACE)

		{

			// if quanity at Prey's location not set
			if(ag_env -> get_quantity(ag_x,ag_y) == 0)
				
			{
			
				// become a space - environment self-adjusting
				ag_type = SPACE;
			
			}

		}
			
		// don't act
		do_nothing();
		return;

	}
	
	// GET RID OF ALL OTHER MOVING TARGETS

	expire_moving_objects();
		
	// OBSERVE THE ENVIRONMENT

	look();

	// if knows of any predators
	if(knows_of(PREDATOR))

	{

		// if can avoid predators
		if(avoid_predators())

		{

			return;

		}

	}

	// if targeting anything
	if(targetting())

	{

		// if can get there
		if(seek_target(ag_target_x,ag_target_y,ag_target_obj))

		{

			return;

		}

	}

	// if unable to wander
	if(!wander(x,y))

	{

		do_nothing();

	}

	// if cant get to wander location
	else if(!seek_target(x,y,SPACE))

	{

		do_nothing();

	}
		
}

bool Prey::avoid_predators()

{

	short x,y,c1,c2,cx,cy,dest;
	short score = 0;
	bool hit = false;

	// if predators exist
	if(knows_of_closest(x,y,PREDATOR))

	{

		// flood at predators location
		update_search_memory();
		execute_search_flood(x,y);

		// set predator location to blocked
		ag_s.put_f(x,y,-1);

		// see if predator can get to prey

		if(ag_s.get_f(ag_x,ag_y) == 0)

		{

			return(false);

		}

		// pick location furthest away as a move

		for(c1 = 0 ; c1 < (MOVE_DIM - 1) ; c1+=2)

		{

			c2 = c1 + 1;

			cx = ag_x + moves_f[c1];
			cy = ag_y + moves_f[c2];

			// if jump location is a valid coordinate
			if(ag_s.check(cx,cy))
		
			{
								
				// if mid point clear
				if(ag_s.get_f(ag_x + moves[c1],ag_y + moves[c2]) > 0)

				{

					// get destination
					dest = ag_s.get_f(cx,cy);
				
					// if destination available and furthest so far
					if(dest > score && dest > 0)

					{
						
						// record this move
						score = dest;
						x = cx;
						y = cy;
						hit = true;
						
					}

				}
						
			}

		}

		// check that we got a move

		if(hit)

		{
			
			// record agent's intended action
			ag_intent.put(JUMP,x,y);
			// record the target - so it shows up in animation
			set_target(x,y,SPACE);
			return(true);
					
		}

		else

		{

			return(false);

		}

	}

	else

	{

		return(false);

	}

}

void Prey::execute_action()

{
		
	if(ag_alive)

	{

		short a, x, y;
		ag_intent.get(a,x,y);
	
		switch(a)

		{

			case NOTHING:

				break;

			case JUMP:

				execute_move();
				break;
			
			case MOVE:

				execute_move();
				break;
			
			default:

				ofstream err("errlog.txt", ios::app);
				err << "\n\nERROR, Prey::execute_action(), Prey " << ag_name << endl;
				err << "attempting to perform illogical action. Action failed!\n";
				err.close();
				break;
					
		}

	}
	
}

void Prey::execute_move()

{
		
	short a,x,y;
	ag_intent.get(a,x,y);	// retrive the action
	short region = ag_env -> get_object_f(x,y);
	
	if(!(a == MOVE || a == JUMP))

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Prey::execute_move(), this function can only handle\n";
		err << "actions that are type MOVE or JUMP.\n";
		err << "Action has FAILED.\n";
		err.close();
		return;

	}

	if(region != SPACE)

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Prey::execute_move(), Prey " << ag_name << " has been allowed to\n";
		err << "move to a blocked region located at (" << x << "," << y << ")\n";
		err << "This region contains identifier " << region << "\n";
		err << "Action has FAILED.\n";
		err << "Prey's coordinates are: " << ag_x << "," << ag_y << "\n";
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