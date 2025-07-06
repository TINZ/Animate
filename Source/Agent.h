//	Filename:		Agent.h
//	Version:		Finale
//	Author:			Paul Tinsley (pmbtin)
//	Date:			19 February, 1999
//	Platform:		Visual C++ 5.00

//	Symbology:		Numbers, functions and data variables are enclosed in
//					square parentheses "[]". This is to remove any
//					ambiguity within the text of comments. All private data
//					member variables are prefixed by "ag_".

//	Errors:			All error messages appended to "errlog.txt".

//	Purpose:		Base class of agents. This class contains the attributes and
//					functionality that are inherent in every agent. All agents
//					must derive from this class.

// Function Comment Style:

// Purpose:			Purpose of the function.
// Preconditions:	What states or conditions must be met before execution
//					of the function.
// Returns:			The object or primitive type that the function returns.
// Side Effects:	Effects that the function may have on private data that
//					are not immediately obvious to the nature of the function.
//					This section may also contain advice and miscellaneous
//					comments.
// Errors:			What type of error is generated, why it is generated and
//					its effects.

#ifndef __AGENT_H
#define __AGENT_H

#include "Environment.h"	// for agents memory, environment access, object/action
							// symbology
#include "Intent.h"			// agents' Intent structure for arbitration
#include "DataStructures.h"	// various useful data structures
#include <fstream>			// errors
#include <stddef.h>			// null definition re pointers and exit
#include <stdlib.h>			// random numbers
#include <algorithm>		// STL container functions

//	*** GLOBALS / TYPE DEFINITIONS ***

// The following are the eight possible movement transitions from any
// coordinate in the grid. [moves_f] represents a faster move

const short MOVE_DIM = 16;
const short moves[MOVE_DIM] = {0,-1,1,-1,1,0,1,1,0,1,-1,1,-1,0,-1,-1};
const short moves_f[MOVE_DIM] = {0,-2,2,-2,2,0,2,2,0,2,-2,2,-2,0,-2,-2};

// UP = X+0, Y-1
// UP-RIGHT = X+1, Y-1
// RIGHT = X+1, Y+0
// DOWN-RIGHT = X+1, Y+1
// DOWN = X+0, Y+1
// DOWN-LEFT = X-1,Y+1
// LEFT = X-1,Y+0
// UP-LEFT = X-1,Y-1

//	*** CLASS DEFINITION ***

class Agent

{

	public:

	//	*** CONSTRUCTORS ***

	Agent() : ag_x(0), ag_y(0), ag_env(NULL), ag_m(40), ag_s(40), ag_name(0),
				ag_v_range(3), ag_type(MINER), ag_alive(true), ag_target_x(0),
				ag_target_y(0), ag_target(false), ag_target_obj(0),
				ag_orig_type(MINER), ag_dim(40), ag_search_prep(false){};
	
	// Purpose:			Default constructor.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	It is important to define values and alter the dimension
	//					of the Agent's memory before using the Agent. See
	//					[reset_environment(args)]. Also see [record_position(args)]
	//					and [init(args)].
	// Errors:			None.

	Agent(const short s, const short x, const short y, Environment *e, const short n,
		const short r, const short t);

	// Purpose:			Creates an Agent. [ag_m] and [ag_s] get [s] as their dimension,
	//					[ag_x] gets [x], [ag_y] gets [y], [ag_env] gets [e], [ag_dim]
	//					gets [s], [ag_name] gets [n], [ag_v_range] gets [r], [ag_type]
	//					gets [t]. The Agent's [ag_intent] is initialised to its current
	//					coordinates	and name with the action [NOTHING]. All elements in
	//					[ag_m] are set to [UNKNOWN]. [erase_target()] is invoked.
	//					[ag_alive] is set to [true].
	// Preconditions:	[s] == [[e] -> get_dim()].
	//					[x] >= 0 && [x] < [[e] -> get_dim()].
	//					[y] >= 0 && [y] < [[e] -> get_dim()].
	//					[e] -> get_object([x],[y]) == [SPACE].
	// Returns:			[Agent].
	// Side Effects:	Agent has not recorded its position in the environment or its memory.
	//					Use [record_position()].
	// Errors:			[errlog] error message if precondition violation. Possible
	//					program exit.
	
	Agent(const Agent &a);

	// Purpose:			Copy constructor.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.
	
	//	*** OPERATORS ***

	virtual Agent & operator =(const Agent &a);
	
	// Purpose:			Destructively assigns [a] to the current context.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	const friend bool operator ==(const Agent &a, const Agent &b)

	// Purpose:			Equality operator.
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	{

		return(a.ag_name == b.ag_name);

	}

	const friend bool operator !=(const Agent &a, const Agent &b)

	// Purpose:			Non-equality operator.
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	{

		return(!(a.ag_name == b.ag_name));

	}

	const friend bool operator <(const Agent &a, const Agent &b)

	// Purpose:			Less-than operator.
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	{
		
		return(a.ag_name < b.ag_name);

	};

	const friend bool operator >(const Agent &a, const Agent &b)

	// Purpose:			Greater-than operator.
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	{
		
		return(a.ag_name > b.ag_name);

	};
	
	//	*** PUBLIC FUNCTION PROTOTYPES ***

	//	** ADMINISTRATION FUNCTIONS **

	virtual void record_position();

	// Purpose:			Agent records its position in the environment and its memory
	//					on the basis of [ag_x] and [ag_y]. It also sets its intent
	//					to [NOTHING] with its current location. Note that the agent
	//					will record its quantity as [1] in [ag_env].
	// Preconditions:	[ag_x] >= 0 && [ag_x] < [[ag_env] -> get_dim()].
	//					[ag_y] >= 0 && [ag_y] < [[ag_env] -> get_dim()].
	//					[ag_env] -> get-object([ag_x],[ag_y]) == [SPACE].
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			[errlog] error message if precondition violation. Possible
	//					program exit.
			
	void get_intent(Intent &i);

	// Purpose:			Loads [i] with [ag_intent], the Agent's intended action.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	void put_intent(Intent i);

	// Purpose:			Loads [ag_intent] with [i], the Agent's intended action.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	Intent get_intent();

	// Purpose:			Returns [ag_intent], the Agent's intended action.
	// Preconditions:	None.
	// Returns:			[Intent].
	// Side Effects:	None.
	// Errors:			None.

	virtual void init(const short n, const short x, const short y, const short t);

	// Purpose:			Sets [ag_name] to [n], [ag_x] to [x], [ag_y] to [y] and
	//					[ag_type] to [t].
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	The Agent's [ag_intent] is totally reset.
	// Errors:			None.

	virtual void init(const short x, const short y);

	// Purpose:			Sets [ag_x] to [x] and [ag_y] to [y].
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	The Agent's [ag_intent] is altered to action [NOTHING]
	//					and the Agent's new coordinates.
	// Errors:			None.
	
	void get_location(short &x, short &y);

	// Purpose:			[x] gets [ag_x], [y] gets [ag_y]. The Agent's current
	//					location.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	virtual void kill();

	// Purpose:			Sets [ag_alive] to [false]. Sets [ag_type] to [CARCASS]. The
	//					value of the [CARCASS] is set to [200].
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	Records new type and quantity in thr environment [ag_env] and
	//					sets action to [NOTHING].
	// Errors:			None.

	const bool is_alive();

	// Purpose:			Returns [ag_alive]. Whether Agent is alive.
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	const short get_name();

	// Purpose:			Returns [ag_name]. The Agent's name.
	// Preconditions:	None.
	// Returns:			[short].
	// Side Effects:	None.
	// Errors:			None.

	const short get_type();

	// Purpose:			Returns [ag_type]. The Agent's type.
	// Preconditions:	None.
	// Returns:			[short].
	// Side Effects:	None.
	// Errors:			None.

	const short get_original_type();

	// Purpose:			Returns [ag_orig_type]. The Agent's type. Agent's type
	//					will change upon death. This is useful in determing what
	//					type it was originally.
	// Preconditions:	None.
	// Returns:			[short].
	// Side Effects:	None.
	// Errors:			None.

	virtual void get_state(short &t, short &n, short &x, short &y, short &a,
							short &q, short &tx, short &ty);
	
	// Purpose:			Loads [t] with [ag_type], [n] with [ag_name], [x] with [ag_x],
	//					[y] with [ag_y], [a] with the action within	[ag_intent]. If
	//					[ag_target] == [true], loads [tx] with [ag_target_x] and [ty]
	//					with [ag_target_y], else both set to [-1]. [q] is set to [0]
	//					but can be overriden to supply a quantity of something that
	//					the agent in carrying or has digested etc.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	void get_environment();

	// Purpose:			Agent loads entire environment [ag_env] into its memory [ag_m].
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None. 
	// Errors:			None.

	// ** BEHAVIOURS AND ABILITIES **

	virtual void think(){ag_search_prep = false;};
	
	// Purpose:			The antecedant/consequant rule/behaviour structure of
	//					the Agent, defined by the user. This is the main control structure
	//					called by the [Administrator].
	// Preconditions:	You must invoke the base definition in a derived object at the start
	//					of the code in your definition. This allows the invariance of
	//					[ag_search_prep] to be maintained.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.
	
	void look();

	// Purpose:			Causes the Agent to look at its environment. Agents have
	//					360 degree vision that has the boundary of a square box
	//					limited by [ag_v_range] centered on the Agent's coordinates.
	//					Agents see everything in the box, whether they know what the
	//					things are is up to you. Agents see regardless of obstacles.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	The Agent's memory [ag_m] is overwritten with the data fetched
	//					from [ag_env] according to the dimensions of the box. Therefore,
	//					the Agent has a subjective view of the world according to what
	//					it last looked at. If the Agent sees its currently targetted
	//					object location and the targetted object is no longer present,
	//					targetting is cancelled ([erase_target()]).
	// Errors:			None.
	
	void set_target(const short x, const short y, const short o);

	// Purpose:			Makes [o] a target. [ag_target_x] gets [x], [ag_target_y] gets [y],
	//					[ag_target_obj] gets [o].
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	void erase_target();

	// Purpose:			[ag_target_x] gets [-1], [ag_target_y] gets [-1],
	//					[ag_target_obj] gets [-1], [ag_target] set to [false].
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	bool seek_target(const short x, const short y, const short o);
	
	// Purpose:			Decide a best move that gets the Agent closer to the
	//					target object [o] located at [x] and [y].
	// Preconditions:	None.
	// Returns:			[bool]. [true] if action is a possible [MOVE], else
	//					[false].
	// Side Effects:	[ag_intent] is set to the best move if returning
	//					[true]. [set_target(args)] is invoked using [x], [y]
	//					and [o] if [true].
	// Errors:			None.
	
	bool targetting();
	
	// Purpose:			Returns [ag_target].
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.
	
	virtual void execute_move();
	
	// Purpose:			Executes a move based on contents of [ag_intent].
	// Preconditions:	[ag_intent] has been arbitrated.
	// Returns:			None.
	// Side Effects:	Agent sets its new position in environment and memory.
	// Errors:			[errlog] message if location specified in [ag_intent] is not
	//					a [SPACE] in [ag_env]. Action fails and [ag_action] set to
	//					[NOTHING].
		
	virtual void execute_action(){};

	// Purpose:			Causes the Agent to execute an action based on the contents
	//					of its [ag_intent].
	// Preconditions:	[ag_intent] has been arbitrated.
	// Returns:			None.
	// Side Effects:	Varies on inherited behaviour.
	// Errors:			None.
	
	void do_nothing();

	// Purpose:			Causes Agent to set its [ag_intent] to [NOTHING] with its
	//					current coordinates [ag_x] and [ag_y]. Agent therefore
	//					intends to do nothing.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.
		
	void expire_moving_objects();

	// Purpose:			All Agents in Agent's memory are deleted and replaced with
	//					[SPACE].
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	bool wander(short &x, short &y);

	// Purpose:			Agent relatively selects a reachable location in its memory
	//					and loads [x] and [y] with the target location as a place to
	//					move towards. [UNKNOWN] regions that are closest have
	//					priority.
	// Preconditions:	None.
	// Returns:			[bool]. [true] if a reachable place is found.
	// Side Effects:	None.
	// Errors:			None.

	bool adjacent_to(const short o);

	// Purpose:			Determines whether the agent is adjacent to the
	//					object [o].
	// Preconditions:	None.
	// Returns:			[bool]. [true] if adjacent.
	// Side Effects:	None.
	// Errors:			None.

	bool adjacent_to(const short x, const short y);

	// Purpose:			Determines whether the agent is adjacent to the
	//					coordinates specified by [x] and [y] by comparison
	//					with [ag_x] and [ag_y].
	// Preconditions:	None.
	// Returns:			[bool]. [true] if adjacent.
	// Side Effects:	None.
	// Errors:			None.

	bool adjacent_to(short &x, short &y, const short o);

	// Purpose:			Determines whether the agent is adjacent to the
	//					coordinates specified by [x] and [y] by comparison
	//					with [ag_x] and [ag_y] and that the location contains
	//					the object [o].
	// Preconditions:	None.
	// Returns:			[bool]. [true] if adjacent.
	// Side Effects:	None.
	// Errors:			None.

	bool knows_of(const short o);

	// Purpose:			Whether the agent knows of object [o], anywhere in
	//					its memory [ag_m].
	// Preconditions:	None.
	// Returns:			[bool]. [true] if [o] found in [ag_m].
	// Side Effects:	None.
	// Errors:			None.

	bool knows_of_closest(short &x, short &y, const short o);

	// Purpose:			If [o] exists in [ag_m], finds the closest [o] and
	//					loads [x] and [y] with its coordinates.
	// Preconditions:	None.
	// Returns:			[bool]. [true] if [o] found in [ag_m].
	// Side Effects:	None.
	// Errors:			None.

	protected:

	//	*** PROTECTED DATA ***

	//	** MEMORY: KNOWN OBJECTS DATA STRUCTURES **
		
	Grid ag_m;						// object memory
	Grid ag_s;						// search memory
	short ag_dim;					// the dimension of memory &
									// environment

	//	** MEMORY: OBJECT TARGETTING AND SEARCH PREPARATION DATA STRUCTURES **

	bool ag_target;					// whether Agent is targetting something
	short ag_target_obj;			// object targetted
	short ag_target_x;				// a target x-coord
	short ag_target_y;				// a target y-coord
	bool ag_search_prep;			// indicates whether total search flood has been
									// performed at agents location. used by knows_of
	
	//	** ENVIRONMENT DATA STRUCTURES **

	Environment *ag_env;			// pointer to Agent's environment
	short ag_x;						// current x-coordinate
	short ag_y;						// current y_coordinate
		
	//	** ATTRIBUTE DATA STRUCTURES **
	
	short ag_type;					// type of Agent
	short ag_orig_type;				// copy of type - used when scenario restarted
	short ag_name;					// name
	short ag_v_range;				// vision range
	bool ag_alive;					// whether Agent is alive
	PATH ag_search;					// used in searching
	
	// ** INTENTION DATA STRUCTURES **

	Intent ag_intent;				// next intended action collected for arbitration
		
	//	*** PROTECTED FUNCTION PROTOTYPES ***
	
	void update_search_memory();

	// Purpose:			Copies [ag_m] to [ag_s] setting all objects to -1, and all
	//					[SPACE] to [0] in [ag_s].
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	void execute_search_flood(short x, short y);
	void execute_partial_search_flood(short x, short y);

	// Purpose:			Floods [ag_s] with values that are representative of the
	//					shortest path to [x] and [y]. The partial version will
	//					only compute as far as it is necessary to plot a path
	//					from the Agent's current coordinates [ag_x] and [ag_y].
	// Preconditions:	[update_search_memory()] has been called.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.
		
	bool next_to(const short x, const short y, const short o);

	// Purpose:			Tests whether [o] is adjacent to [x] and [y]. This
	//					is used to find unknown areas, [UNKNOWN], in [ag_m].
	// Preconditions:	None.
	// Returns:			[bool]. [true] if [o] is adjacent.
	// Side Effects:	None.
	// Errors:			None.
	
};

#endif