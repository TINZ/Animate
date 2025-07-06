//	Filename:		Predator.h
//	Version:		Final
//	Author:			Paul Tinsley (pmbtin)
//	Date:			26 February, 1999
//	Platform:		Visual C++ 5.00

//	Symbology:		Numbers, functions and data variables are enclosed in
//					square parentheses "[]". This is to remove any
//					ambiguity within the text of comments. All private data
//					member variables are prefixed by "p_".

//	Errors:			All error messages appended to "errlog.txt".

//	Purpose:		Predator agents.

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

//	Refer to Agent.h for details of some functions.

#ifndef __PREDATOR_H
#define __PREDATOR_H

#include "Agent.h"		// base class
#include <fstream>		// error logs

class Predator : public Agent

{

	public:

	// *** CONSTRUCTORS ***

	Predator(): Agent(), p_stomach(0), p_stomach_max(10){};

	// Purpose:			Default constructor.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	Predator(const short s, const short x, const short y, Environment *e, const short n,
				const short r, const short stom, const short stom_m)
				: Agent(s,x,y,e,n,r,PREDATOR), p_stomach(stom), p_stomach_max(stom_m){};
	
	// Purpose:			Constructor. See base constructor. [p_stomach] gets [stom] and
	//					p_stomach_max gets [stom_m].
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	//	*** OPERATORS ***

	virtual Predator & operator =(const Predator &a);
	
	// Purpose:			Destructively assigns [a] to the current context.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	const friend bool operator ==(const Predator &a, const Predator &b)

	// Purpose:			Equality operator.
	// Preconditions:	None.
	// Returns:			[bool] [true]/[false].
	// Side Effects:	None.
	// Errors:			None.

	{

		return(a.ag_name == b.ag_name);

	}

	const friend bool operator !=(const Predator &a, const Predator &b)

	// Purpose:			Non-equality operator.
	// Preconditions:	None.
	// Returns:			[bool] [true]/[false].
	// Side Effects:	None.
	// Errors:			None.

	{

		return(!(a.ag_name == b.ag_name));

	}

	const friend bool operator <(const Predator &a, const Predator &b)

	// Purpose:			Less-than operator. An agent is less than another
	//					agent if its name is less in value.
	// Preconditions:	None.
	// Returns:			[bool] [true]/[false].
	// Side Effects:	None.
	// Errors:			None.

	{
		
		return(a.ag_name < b.ag_name);

	};

	const friend bool operator >(const Predator &a, const Predator &b)

	// Purpose:			Greater-than operator. An agent is greater than another
	//					agent if its name is greater in value.
	// Preconditions:	None.
	// Returns:			[bool] [true]/[false].
	// Side Effects:	None.
	// Errors:			None.

	{
		
		return(a.ag_name > b.ag_name);

	};

	//	*** PUBLIC FUNCTION PROTOTYPES ***

	virtual void get_state(short &t, short &n, short &x, short &y, short &a, short &q,
					short &tx, short &ty);
	
	// BASE OVERRIDE

	// Purpose:			Loads [t] with [ag_type], [n] with [ag_name], [x] with [ag_x],
	//					[y] with [ag_y], [a] with the action within	[ag_intent]. [q]
	//					gets [p_stomach]. If [ag_target] == [true], loads [tx] with
	//					[ag_target_x] and [ty] with [ag_target_y], else both set to [-1].
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	virtual void think();

	// Purpose:			The behavioural definition rules for these Predators.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	virtual void execute_action();

	// Purpose:			Causes the Predator to execute an action based on the contents
	//					of its [ag_intent].
	// Preconditions:	[ag_intent] has been arbitrated.
	// Returns:			None.
	// Side Effects:	The Predator may effect the environment [ag_env].
	// Errors:			None.

	void feed(const short x, const short y);

	// Purpose:			If a [CARCASS] exists at ([x],[y]) in [ag_env] and
	//					Predator is adjacent to it, sets [ag_intent] to
	//					action [GRAB] at those coordinates.
	// Preconditions:	[ag_env -> get_object([x],[y]) == CARCASS] &&
	//					adjacent_to([x],[y]).
	// Returns:			None.
	// Side Effects:	[erase_target] called if successful.
	// Errors:			[errlog] message if precondition violation. [ag_intent]
	//					set to [do_nothing].

	void pounce(const short x, const short y);

	// Purpose:			If a [PREY] exists at ([x],[y]) in [ag_env] and
	//					Predator is adjacent to it, sets [ag_intent] to
	//					action [POUNCE] at those coordinates.
	// Preconditions:	[ag_env -> get_object([x],[y]) == PREY] &&
	//					adjacent_to([x],[y]).
	// Returns:			None.
	// Side Effects:	[erase_target] called if successful.
	// Errors:			[errlog] message if precondition violation. [ag_intent]
	//					set to [do_nothing].

	void execute_feed(const short x, const short y);

	// Purpose:			If a [CARCASS] exists at ([x],[y]) in [ag_env] then
	//					Predator feeds from it and increases [p_stomach] up
	//					to a max value of [p_stomach_max].
	// Preconditions:	[ag_env -> get_object([x],[y]) == CARCASS]
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	const bool hungry();

	// Purpose:			Returns whether [p_stomach] != [p_stomach_max].
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.
	
	private:

	short p_stomach;		// stomach contents
	short p_stomach_max;	// max stomach contents
	
};

#endif