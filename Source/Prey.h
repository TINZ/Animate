//	Filename:		Prey.h
//	Version:		Final
//	Author:			Paul Tinsley (pmbtin)
//	Date:			26 February, 1999
//	Platform:		Visual C++ 5.00

//	Symbology:		Numbers, functions and data variables are enclosed in
//					square parentheses "[]". This is to remove any
//					ambiguity within the text of comments.

//	Errors:			All error messages appended to "errlog.txt".

//	Purpose:		Prey agents. Derived from Agent.h.

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

#ifndef __PREY_H
#define __PREY_H

#include "Agent.h"			// base class
#include <fstream>			// error logs

class Prey : public Agent

{

	public:

	// *** CONSTRUCTORS ***

	Prey(): Agent(){};

	// Purpose:			Default constructor.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	Prey(const short s, const short x, const short y, Environment *e, const short n,
			const short r) : Agent(s,x,y,e,n,r,PREY){};
	
	// Purpose:			Constructor. See base class definitions.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	//	*** OPERATORS ***

	const friend bool operator ==(const Prey &a, const Prey &b)

	// Purpose:			Equality operator.
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	{

		return(a.ag_name == b.ag_name);

	}

	const friend bool operator !=(const Prey &a, const Prey &b)

	// Purpose:			Non-equality operator.
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	{

		return(!(a.ag_name == b.ag_name));

	}

	const friend bool operator <(const Prey &a, const Prey &b)

	// Purpose:			Less-than operator. An agent is less than another
	//					agent if its name is less in value.
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	{
		
		return(a.ag_name < b.ag_name);

	};

	const friend bool operator >(const Prey &a, const Prey &b)

	// Purpose:			Greater-than operator. An agent is greater than another
	//					agent if its name is greater in value.
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	{
		
		return(a.ag_name > b.ag_name);

	};

	//	*** PUBLIC FUNCTION PROTOTYPES ***

	virtual void get_state(short &t, short &n, short &x, short &y, short &a, short &q,
					short &tx, short &ty);
		
	// Purpose:			Loads [t] with [ag_type], [n] with [ag_name], [x] with [ag_x],
	//					[y] with [ag_y], [a] with the action within	[ag_intent]. [q]
	//					gets [ag_env -> get_quantity_f(ag_x,ag_y)]. If [ag_target]
	//					== [true], loads [tx] with [ag_target_x] and [ty] with
	//					[ag_target_y], else both set to [-1].
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	virtual void think();

	// Purpose:			The behavioural rules of a Prey agent.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	virtual void execute_action();

	// Purpose:			Causes the Prey to execute an action based on the contents
	//					of its [ag_intent].
	// Preconditions:	[ag_intent] has been arbitrated.
	// Returns:			None.
	// Side Effects:	The Prey may affect the environment [ag_env].
	// Errors:			None.

	virtual void execute_move();
	
	// Purpose:			Executes a move based on contents of [ag_intent]. Required
	//					to handle definition of [JUMP].
	// Preconditions:	[ag_intent] has been arbitrated.
	// Returns:			None.
	// Side Effects:	Prey sets its new position in environment and memory.
	// Errors:			[errlog] message if location specified in [ag_intent] is not
	//					a [SPACE] in [ag_env]. Action fails and [ag_action] set to
	//					[NOTHING].
		
	private:
	
	bool avoid_predators();

	// Purpose:			If Predators detected, builds a [JUMP] move that gets the
	//					Prey away from the closest threat.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	If succesful, [ag_intent] is updated with a [JUMP] move.
	// Errors:			None.
	
};

#endif