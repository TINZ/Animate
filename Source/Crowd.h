//	Filename:		Crowd.h
//	Version:		Final
//	Author:			Paul Tinsley (pmbtin)
//	Date:			26 February, 1999
//	Platform:		Visual C++ 5.00

//	Symbology:		Numbers, functions and data variables are enclosed in
//					square parentheses "[]". This is to remove any
//					ambiguity within the text of comments.

//	Errors:			All error messages appended to "errlog.txt".

//	Purpose:		Crowd Agents. Used to illustrate how crowd behaviours
//					may be implemented and investigated.

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

#ifndef __CROWD_H
#define __CROWD_H

#include "Agent.h"

class Crowd : public Agent

{

	public:


	// *** CONSTRUCTORS ***

	Crowd(): Agent(){};

	// Purpose:			Default constructor.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	Crowd(short s,short x,short y,Environment *e,short n,short r)
		:Agent(s,x,y,e,n,r,MINER){};
	
	// Purpose:			Constructor. See base constructor definition in
	//					[Agent::Agent(args)].
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	//	*** OPERATORS ***
	
	const friend bool operator ==(const Crowd &a, const Crowd &b)

	// Purpose:			Equality operator.
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	{

		return(a.ag_name == b.ag_name);

	}

	const friend bool operator !=(const Crowd &a, const Crowd &b)

	// Purpose:			Non-equality operator.
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	{

		return(!(a.ag_name == b.ag_name));

	}

	const friend bool operator <(const Crowd &a, const Crowd &b)

	// Purpose:			Less-than operator. An agent is less than another
	//					agent if its name is less in value.
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	{
		
		return(a.ag_name < b.ag_name);

	};

	const friend bool operator >(const Crowd &a, const Crowd &b)

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

	virtual void think();
	
	// Purpose:			The behavioural rules for these Crowd agents.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	virtual void execute_action();

	// Purpose:			Causes the Crowd agent to execute an action based on the contents
	//					of its [ag_intent].
	// Preconditions:	[ag_intent] has been arbitrated.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.
	
	virtual void kill();

	// Purpose:			Sets [ag_alive] to [false]. Sets [ag_type] to [SPACE].
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	Records new type and quantity in the environment [ag_env] and
	//					sets action to [NOTHING].
	// Errors:			None.
	
};

#endif