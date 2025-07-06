//	Filename:		Adminitrator.h
//	Version:		Final
//	Author:			Paul Tinsley (pmbtin)
//	Date:			26 February, 1999
//	Platform:		Visual C++ 5.00

//	Symbology:		Numbers, functions and data variables are enclosed in
//					square parentheses "[]". This is to remove any
//					ambiguity within the text of comments. All private data
//					member variables are prefixed by "ad_".

//	Errors:			All error messages appended to "errlog.txt"

//	Purpose:		Administrates over a collection of possibly heterogeneous
//					agents derived from a common base class. The functionality
//					allows a turn-based control and thus the order of calls
//					is important. Various access functions allow data to be
//					gathered for experiments and animation. The Administrator
//					is capable of generating a script that contains the state
//					of all objects that may be used for animation and also
//					information processing, such as plotting tracks of agents
//					through the environment.

//	Function Comment Style:

//	Purpose:		Purpose of the function.
//	Preconditions:	What states or conditions must be met before execution
//					of the function.
//	Returns:		The object or primitive type that the function returns.
//	Side Effects:	Effects that the function may have on private data that
//					are not immediately obvious to the nature of the function.
//					This section may also contain advice and miscellaneous
//					comments.
//	Errors:			What type of error is generated, why it is generated and
//					its effects.

//	Scripts:

/*

	Scripts are vector containers of the class [chunk]. Their organisation is
	as follows:

	TURN n:

	info field (1,number of frames for turn n,0,0,0,0,0,0,0)
	anim frame (0,ads_type,ads_name,ads_x,ads_y,ads_action,ads_quantity,ads_target_x,
				ads_target_y)
	.
	.
	.
	.
	TURN n+1:
	info field (1,number of frames for turn n+1,0,0,0,0,0,0,0)
	anim frame .....
	.
	.
	.

*/

//	Example scenario control loop. The administrator instance is [admin]:

/*

	** START TURN **

	admin.deliberate();			// invoke [think()] in every agent
			
	admin.get_intentions();		// collect intended actions from agents
			
	admin.arbitrate();			// arbitrate the actions using the arbitrator class
		
	*** SPECIAL EVENTS ***		// place special functions here to handle scenario
								// specific events. You can intercept the writing
								// back of agents' intentions.

	admin.set_intentions();		// write back the intentions to the agents
			
	admin.execute_actions();	// invoke [execute_action()] in every agent
			
	admin.update_script();		// if creating an animation script, place the
								// call here

	** END TURN **

*/

#ifndef __ADMINISTRATOR_H
#define __ADMINISTRATOR_H

#include "Agent.h"					// base class of agents
#include "Miner.h"					// basic mining agents
#include "ChainMiner.h"				// chain mining agents
#include "Predator.h"				// predator agents
#include "Prey.h"					// prey agents
#include "Crowd.h"					// crowd agents
#include "Intent.h"					// agents intentions
#include "Arbitrator.h"				// the arbitrator
#include "DataStructures.h"			// various data structures / types
#include <time.h>					// to seed random number generator
#include <stddef.h>					// for program exit
#include <vector>					// containers of agents

using namespace std;

typedef vector<Agent*> AGENTS;			// agents derived from a base class
typedef AGENTS :: iterator AGENTS_IT;

// Note - vector contains pointers to a base class, therefore derived
// members pointed to in a filled vector are dynamically binded via
// virtual functions and the inheritance tree

//	*** CLASS DEFININTION ***

class Administrator

{

	public:

	//	*** CONSTRUCTOR ***

	Administrator(); 
	
	// Purpose:			Default constructor. All [Administrator] instances have a
	//					two-stage construction process. Use the specific setup
	//					function for the type of scenario being used.
	// Preconditions:	None.
	// Returns:			[Administrator] object.
	// Side Effects:	1st stage of 2 stage construction.
	// Errors:			None.
	
	//	*** DESTRUCTOR ***

	~Administrator();

	// Purpose:			Releases any memory allocated through the base class
	//					[Agent] pointers in [ad_agents].
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.
	
	//	*** PUBLIC FUNCTION PROTOTYPES ***

	bool setup_miner1(const bool explore, const short miners, const short miner_r,
						const short grab, const short sack, const short grid_size,
						ifstream &m);

	// Purpose:			Second stage construction for the basic mining experiment.
	//					[explore] reflects whether agents will aready know their
	//					environment, [true] is they do not. [miners] is the number
	//					of basic mining agents. [miner_r] is the mining agents' visual
	//					range. [grab] is the miners' grabbing capacity. [sack] is the
	//					miners' sack contents capacity. [grid_size] is the dimension
	//					of the environment contained in the stream [m].
	// Preconditions:	At least one miner up to as many as you like. [m] must contain
	//					environment map data and meet the preconditions set out in
	//					[Grid::input(ifstream &in)].
	// Returns:			Setup will return [false] if there is not enough space in the
	//					environment to place the miners or [miners] <= 0.
	// Side Effects:	2nd stage of 2 stage construction.
	// Errors:			[errlog] messages if not enough space for agents, or the map
	//					file stream or map data is invalid, or [miners] <= 0. Returns
	//					[false].
		
	bool setup_miner2(const bool explore, const short miners, const short miner_r,
						const short grab, const short sack, const short grid_size,
						ifstream &m);

	// Purpose:			Second stage construction for the chain-mining experiment.
	//					[explore] reflects whether agents will aready know their
	//					environment, [true] is they do not. [miners] is the number
	//					of chain-mining agents. [miner_r] is the mining agents' visual
	//					range. [grab] is the miners' grabbing capacity. [sack] is the
	//					miners' sack contents capacity. [grid_size] is the dimension
	//					of the environment contained in the stream [m].
	// Preconditions:	At least one miner up to as many as you like. [m] must contain
	//					environment map data and meet the preconditions set out in
	//					[Grid::input(ifstream &in)].
	// Returns:			Setup will return [false] if there is not enough space in the
	//					environment to place the miners or [miners] <= 0.
	// Side Effects:	2nd stage of 2 stage construction.
	// Errors:			[errlog] messages if not enough space for agents, or the map
	//					file stream or map data is invalid, or [miners <= 0]. Returns
	//					[false].
	
	bool setup_hunting(const bool explore, const short predators, const short prey,
						const short predator_r, const short prey_r,	const short stom,
						const short stom_max, const short grid_size, ifstream &m);

	// Purpose:			Second stage construction for the predator & prey experiment.
	//					[explore] reflects whether agents will aready know their
	//					environment, [true] is they do not. [predators] is the number
	//					of predator agents. [prey] is the number of prey agents.
	//					[predator_r] is the predator agents' visual	range. [prey_r] is
	//					the prey agents' visual range. [stom] is the predators' initial
	//					stomach contents. [stom_max] is the predators' maximum stomach
	//					capacity. [grid_size] is the dimension of the environment
	//					contained in the stream [m].
	// Preconditions:	At least one agent per category up to as many as you like. [m]
	//					must contain environment map data and meet the preconditions
	//					set out in [Grid::input(ifstream &in)].
	// Returns:			Setup will return [false] if there is not enough space in the
	//					environment to place the agents or [predators+prey] <= 0.
	// Side Effects:	2nd stage of 2 stage construction.
	// Errors:			[errlog] messages if not enough space for agents, or the map
	//					file stream or map data is invalid, or [predators <= 0], or
	//					[prey <= 0]. Returns [false].

	bool setup_crowd1(const bool explore,const short crowders,const short crowder_r,
						const short grid_size,ifstream &m);

	// Purpose:			Second stage construction for the crowd experiment.
	//					[explore] reflects whether agents will aready know their
	//					environment, [true] is they do not. [crowders] is the number
	//					of crowd agents. [crowder_r] is the crowd agents' visual
	//					range. [grid_size] is the dimension of the environment
	//					contained in the stream [m].
	// Preconditions:	At least one crowd agent up to as many as you like. [m]
	//					must contain environment map data and meet the preconditions
	//					set out in [Grid::input(ifstream &in)].
	// Returns:			Setup will return [false] if there is not enough space in the
	//					environment to place the crowders or [crowders] <= 0..
	// Side Effects:	2nd stage of 2 stage construction.
	// Errors:			[errlog] messages if not enough space for agents, or the map
	//					file stream or map data is invalid, or [crowders] <= 0. Returns
	//					[false].
		
	void check_hunting_POUNCE();

	// Purpose:			Special function for the hunting experiment. If a Predator
	//					agent has the action [POUNCE], searches for the Prey that
	//					was pounced on and rolls random death. Predator has a 40%
	//					chance of killing Prey. If Prey killed, Administrator invokes
	//					the [kill()] function for the Prey and sets its action to
	//					[NOTHING].
	// Preconditions:	[ad_intents] have been arbitrated.
	// Returns:			None.
	// Side Effects:	See purpose.
	// Errors:			None.
		
	void deliberate();

	// Purpose:			Executes the [think()] function for every agent.
	// Preconditions:	Agents must exist!
	// Returns:			None.
	// Side Effects:	Agents deliberate and set their intentions.
	// Errors:			None.

	void get_intentions();

	// Purpose:			Collects all agents' intentions into [ad_intents].
	// Preconditions:	Only makes sense to use this if initial turn or just
	//					deliberated.
	// Returns:			None.
	// Side Effects:	[ad_intents] is loaded with new data.
	// Errors:			None.

	void set_intentions();

	// Purpose:			Copies the [ad_intents] back to each agent.
	// Preconditions:	The [ad_intents] have been arbitrated.
	// Returns:			None.
	// Side Effects:	Agent's intentions may have been changed by arbitration.
	// Errors:			None.

	void execute_actions();

	// Purpose:			Triggers the [execute_action()] function within every agent.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	Agents execute their intention and may effect the environment.
	// Errors:			None.
	
	void update_script();
	
	// Purpose:			Gets the state of each agent and every object exluding
	//					[OBSTACLE].	Updates [ad_script] and [ad_last_script].
	// Preconditions:	Agents have just executed their actions [execute_actions()].
	// Returns:			None.
	// Side Effects:	[ad_script] gets longer, [ad_last_script] is replaced.
	// Errors:			None.
		
	void arbitrate();

	// Purpose:			Hands [ad_intents] to the arbitrator for arbitration.
	// Preconditions:	[ad_intents] must have been loaded with each agent's intent
	//					after deliberation.
	// Returns:			None.
	// Side Effects:	Arbitrator may change the intents.
	// Errors:			None.
		
	void get_script(SCRIPT &s);

	// Purpose:			Returns [ad_script]. This script contains the state of
	//					every object for every executed turn.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	void get_last_turn(SCRIPT &s);

	// Purpose:			Returns [ad_last_script]. This script contains the state of
	//					every object for the last executed turn.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.
	
	private:

	//	*** PRIVATE DATA MEMBERS ***

	AGENTS ad_agents;			// pointer collection of agents
	Environment ad_env;			// the environment
	short ad_dim;				// environment dimension
	INTENT_LIST ad_intents;		// agents' intentions
	Arbitrator ad_arb;			// the arbitrator
	long ad_script_pos;			// where we are up to in the script
	SCRIPT ad_script;			// to hold data for animation script
	SCRIPT ad_last_script;		// last turns script - only data for that turn
	
	// private data invloved with creating animation scripts
	// ordering is important when written into the type [chunk] within the script

	short ads_type;				// type of object
	short ads_name;				// object name if agent, else 0
	short ads_x;				// current x-coord of object
	short ads_y;				// current y-coord of object
	short ads_action;			// current action if agent
	short ads_quantity;			// quantity of object or quantity carried by agent
	short ads_target_x;			// current agent targetted x-coord
	short ads_target_y;			// current agent targetted y-coord

	void deallocate_agents();

	// Purpose:			De-allocates agents in [ad_agents].
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

};

#endif