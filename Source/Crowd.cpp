//	Filename:		Crowd.cpp
//	Version:		Final
//	Author:			Paul Tinsley (pmbtin)
//	Date:			26 February, 1999
//	Platform:		Visual C++ 5.00

//	Purpose:		See Crowd.h. Derived from base class Agent.h.

//	Refer to Agent.h for details of some functions.

#include "stdafx.h"
#include "Crowd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	*** PUBLIC FUNCTIONS **

void Crowd::think()

{

	if(!is_alive())

	{

		do_nothing();
		return;

	}

	Agent::think();

	short x,y;
	
	// REMOVE ALL MOBILE AGENTS FROM MEMORY

	expire_moving_objects();
		
	// OBSERVE THE ENVIRONMENT

	look();

	// DISSAPEAR WHEN AT EXIT

	if(adjacent_to(HOME))

	{

		kill();
		do_nothing();
		return;

	}

	// GET TO THE HOME - MAKE SURE ALWAYS CLOSEST KNOWN

	if(ag_target_obj != HOME && knows_of(HOME))

	{

		if(knows_of_closest(x,y,HOME))

		{

			if(seek_target(x,y,HOME))
				
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

	if(wander(x,y))

	{

		if(seek_target(x,y,SPACE))
			
		{
			
			return;

		}

	}

	do_nothing();

}

void Crowd::execute_action()

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
			
			default:

				ofstream err("errlog.txt", ios::app);
				err << "\n\nERROR, Crowd::execute_action(), Crowder " << ag_name << endl;
				err << "attempting to perform illogical action. Action failed!\n";
				err.close();
				break;
					
		}

	}
	
}

void Crowd::kill()

{

	ag_alive = false;
	ag_type = SPACE;
	ag_env -> put_object_f(ag_x,ag_y,ag_type,0);

}