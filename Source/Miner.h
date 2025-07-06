//	Filename:		Miner.h
//	Version:		Final
//	Author:			Paul Tinsley (pmbtin)
//	Date:			26 February, 1999
//	Platform:		Visual C++ 5.00

//	Symbology:		Numbers, functions and data variables are enclosed in
//					square parentheses "[]". This is to remove any
//					ambiguity within the text of comments. All private data
//					member variables are prefixed by "m_".

//	Errors:			All error messages appended to "errlog.txt".

//	Purpose:		Basic Mining Agents. Derived from Agent.h.

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

#ifndef __MINER_H
#define __MINER_H

#include "Agent.h"

class Miner : public Agent

{

	public:


	// *** CONSTRUCTORS ***

	Miner(): Agent(), m_sack(0), m_sack_max(50), m_scoop(10) {};

	// Purpose:			Default constructor.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	Miner(short s, short x, short y, Environment *e, short n, short r, short sm, short sc)
		:Agent(s, x, y, e, n, r, MINER), m_sack(0), m_sack_max(sm), m_scoop(sc) {};
	
	// Purpose:			Constructor. See base constructor definition in [Agent::Agent(args)].
	//					[m_sack_max] records the maximum sack capacity. [m_scoop] records
	//					the amount of minerals that a Miner can mine in one turn. [m_sack]
	//					is the current mineral quantity being carried.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	//	*** OPERATORS ***

	virtual Miner & operator =(const Miner &a);
	
	// Purpose:			Destructively assigns [a] to the current context.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	const friend bool operator ==(const Miner &a, const Miner &b)

	// Purpose:			Equality operator.
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	{

		return(a.ag_name == b.ag_name);

	}

	const friend bool operator !=(const Miner &a, const Miner &b)

	// Purpose:			Non-equality operator.
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	{

		return(!(a.ag_name == b.ag_name));

	}

	const friend bool operator <(const Miner &a, const Miner &b)

	// Purpose:			Less-than operator. An agent is less than another
	//					agent if its name is less in value.
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	{
		
		return(a.ag_name < b.ag_name);

	};

	const friend bool operator >(const Miner &a, const Miner &b)

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
	//					gets [m_sack]. If [ag_target] == [true], loads [tx] with
	//					[ag_target_x] and [ty] with [ag_target_y], else both set to [-1].
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	virtual void think();
	
	// Purpose:			The behavioural definition rules for these Miners.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	virtual void execute_action();

	// Purpose:			Causes the Miner to execute an action based on the contents
	//					of its [ag_intent].
	// Preconditions:	[ag_intent] has been arbitrated.
	// Returns:			None.
	// Side Effects:	The Miner may effect the environment [ag_env].
	// Errors:			None.

	private:

	//	*** PRIVATE DATA MEMBERS ***

	short m_sack;			// a sack for carrying things
	short m_sack_max;		// max capacity of sack
	short m_scoop;			// max amount Miner can scoop in one turn

	//	*** PRIVATE FUNCTION PROTOTYPES ***

	void execute_mine_minerals(const short x, const short y);
	
	// Purpose:			The Miner will mine minerals from the location
	//					([x],[y]) increasing the quantity in [m_sack].
	// Preconditions:	The intended action has been arbitrated. The Miner
	//					is adjacent to ([x],[y]). [m_sack] != [m_sack_max].
	//					Minerals [MINERAL] exist at ([x],[y]).
	// Returns:			None.
	// Side Effects:	The Miner may effect the environment [ag_env].
	// Errors:			[errlog] messages if preconditions violated. Miner's
	//					action may be cancelled and replaced with the action
	//					[do_nothing()].

	void execute_empty_backpack(const short x, const short y);

	// Purpose:			The Miner will empty the contents of [m_sack] in the
	//					location ([x],[y]).
	// Preconditions:	The intended action has been arbitrated. The Miner
	//					is adjacent to ([x],[y]). [m_sack] != 0. ([x],[y])
	//					is a [HOME].
	// Returns:			None.
	// Side Effects:	If insufficient space, an [errlog] message will be
	//					generated and the action will fail.
	// Errors:			[errlog] messages if preconditions violated. Miner's
	//					action may be cancelled and replaced with the action
	//					[do_nothing()].

	void mine_minerals(const short x, const short y);

	// Purpose:			The Miner will set [ag_intent] to relect the taking
	//					of minerals from ([x],[y]).
	// Preconditions:	The Miner is adjacent to ([x],[y]). [m_sack] != [m_sack_max].
	//					Minerals [MINERAL] exist at ([x],[y]).
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			[errlog] messages if preconditions violated. Miner's
	//					action may be cancelled and replaced with the action
	//					[do_nothing()].

	void empty_backpack(const short x, const short y);
	
	// Purpose:			The Miner will set [ag_intent] to relect the dropping
	//					of minerals at location ([x],[y]).
	// Preconditions:	The Miner is adjacent to ([x],[y]). [m_sack] != 0.
	//					([x],[y]) is a [HOME].
	// Returns:			None.
	// Side Effects:	If insufficient space, an [errlog] message will be
	//					generated and the action will fail.
	// Errors:			[errlog] messages if preconditions violated. Miner's
	//					action may be cancelled and replaced with the action
	//					[do_nothing()].

	const bool sack_full();

	// Purpose:			Returns whether [m_sack] == [m_sack_max].
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	const bool sack_empty();

	// Purpose:			Returns whether [m_sack] == [0].
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	const short sack_space();

	// Purpose:			Returns space remaining in [m_sack].
	// Preconditions:	None.
	// Returns:			[short].
	// Side Effects:	None.
	// Errors:			None.

};

#endif