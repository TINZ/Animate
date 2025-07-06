//	Filename:		ChainMiner.h
//	Version:		Final
//	Author:			Paul Tinsley (pmbtin)
//	Date:			26 February, 1999
//	Platform:		Visual C++ 5.00 Console Application, release build

//	Refer to Agent.h for details of some functions.

//	Symbology:		Numbers, functions and data variables are enclosed in
//					square parentheses "[]". This is to remove any
//					ambiguity within the text of comments. All private data
//					member variables are prefixed by "cm_".

//	Errors:			All error messages appended to "errlog.txt".

//	Purpose:		Chain-Mining Agents. Derived from Agent.h.

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

#ifndef __CHAINMINER_H
#define __CHAINMINER_H

#include "Agent.h"
#include <fstream>

class ChainMiner : public Agent

{

	public:


	// *** CONSTRUCTORS ***

	ChainMiner(): Agent(), cm_sack(0), cm_sack_max(50), cm_scoop(10),
					cm_endurance(12), cm_facing(0){};

	// Purpose:			Default constructor.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	ChainMiner(short s, short x, short y, Environment *e, short n, short r,
				short sm, short sc) : Agent(s,x,y,e,n,r,MINER), cm_sack(0),
				cm_sack_max(sm), cm_scoop(sc), cm_endurance(12), cm_facing(0){};
	
	// Purpose:			Constructor. See base class constructor. [cm_sack] is
	//					the ChainMiner's current backpack contents, [cm_sack_max]
	//					is the maximum backpack contents, [cm_scoop] is the
	//					maximum amount that can be grabbed in a turn and
	//					[cm_endurance] is the current energy level.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	//	*** OPERATORS ***

	virtual ChainMiner & operator =(const ChainMiner &a);
	
	// Purpose:			Destructively assigns [a] to the current context.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	const friend bool operator ==(const ChainMiner &a, const ChainMiner &b)

	// Purpose:			Equality operator.
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	{

		return(a.ag_name == b.ag_name);

	}

	const friend bool operator !=(const ChainMiner &a, const ChainMiner &b)

	// Purpose:			Non-equality operator.
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	{

		return(!(a.ag_name == b.ag_name));

	}

	const friend bool operator <(const ChainMiner &a, const ChainMiner &b)

	// Purpose:			Less-than operator. An agent is less than another
	//					agent if its name is less in value.
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	{
		
		return(a.ag_name < b.ag_name);

	};

	const friend bool operator >(const ChainMiner &a, const ChainMiner &b)

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
	// BASE OVERRIDE

	// Purpose:			Loads [t] with [ag_type], [n] with [ag_name], [x] with [ag_x],
	//					[y] with [ag_y], [a] with the action within	[ag_intent]. [q]
	//					gets [cm_sack]. If [ag_target] == [true], loads [tx] with
	//					[ag_target_x] and [ty] with [ag_target_y], else both set to [-1].
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	virtual void think();

	// Purpose:			The behavioural definition rules for these ChainMiners.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	virtual void execute_action();

	// Purpose:			Causes the ChainMiner to execute an action based on the contents
	//					of its [ag_intent].
	// Preconditions:	[ag_intent] has been arbitrated.
	// Returns:			None.
	// Side Effects:	The ChainMiner agent may affect the environment [ag_env].
	// Errors:			None.
			
	private:

	void execute_mine_minerals(const short x, const short y);

	// Purpose:			The ChainMiner will mine minerals from the location
	//					([x],[y]) increasing the quantity in [cm_sack].
	// Preconditions:	The intended action has been arbitrated. The ChainMiner
	//					is adjacent to ([x],[y]). [cm_sack] != [cm_sack_max].
	//					Minerals [MINERAL] exist at ([x],[y]).
	// Returns:			None.
	// Side Effects:	The Chain Miner may affect the environment [ag_env].
	// Errors:			[errlog] messages if preconditions violated. ChainMiner's
	//					action may be cancelled and replaced with the action
	//					[do_nothing()].

	void execute_grab_ore(const short x, const short y);

	// Purpose:			The ChainMiner will grab ore from the location
	//					([x],[y]) increasing the quantity in [cm_sack].
	// Preconditions:	The intended action has been arbitrated. The ChainMiner
	//					is adjacent to ([x],[y]). [cm_sack] != [cm_sack_max].
	//					Ore [ORE] exist at ([x],[y]).
	// Returns:			None.
	// Side Effects:	The Chain Miner may affect the environment [ag_env].
	// Errors:			[errlog] messages if preconditions violated. ChainMiner's
	//					action may be cancelled and replaced with the action
	//					[do_nothing()].

	void execute_empty_backpack(const short x, const short y);

	// Purpose:			The ChainMiner will empty the contents of [m_sack] in the
	//					location ([x],[y]).
	// Preconditions:	The intended action has been arbitrated. The ChainMiner
	//					is adjacent to ([x],[y]). [cm_sack] != 0. ([x],[y])
	//					is a [HOME] or [ORE] or [SPACE].
	// Returns:			None.
	// Side Effects:	If insufficient space, an [errlog] message will be
	//					generated and the action will fail.
	// Errors:			[errlog] messages if preconditions violated. ChainMiner's
	//					action may be cancelled and replaced with the action
	//					[do_nothing()].

	void mine_minerals(const short x, const short y);

	// Purpose:			The ChainMiner will set [ag_intent] to relect the taking
	//					of minerals from ([x],[y]).
	// Preconditions:	The ChainMiner is adjacent to ([x],[y]). [cm_sack] !=
	//					[cm_sack_max].
	//					Minerals [MINERAL] exist at ([x],[y]).
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			[errlog] messages if preconditions violated. ChainMiner's
	//					action may be cancelled and replaced with the action
	//					[do_nothing()].

	void empty_backpack(const short x, const short y);

	// Purpose:			The ChainMiner will set its [ag_intent] to relect the
	//					dropping of minerals at location ([x],[y]).
	// Preconditions:	The Miner is adjacent to ([x],[y]). [cm_sack] != 0.
	//					([x],[y]) is a [HOME] or [SPACE] or [ORE].
	// Returns:			None.
	// Side Effects:	If insufficient space, an [errlog] message will be
	//					generated and the action will fail.
	// Errors:			[errlog] messages if preconditions violated. ChainMiner's
	//					action may be cancelled and replaced with the action
	//					[do_nothing()].

	void grab_ore(const short x, const short y);

	// Purpose:			The ChainMiner will set [ag_intent] to relect the taking
	//					of ore from ([x],[y]).
	// Preconditions:	The ChainMiner is adjacent to ([x],[y]). [cm_sack] !=
	//					[cm_sack_max].
	//					Ore [ORE] exist at ([x],[y]).
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			[errlog] messages if preconditions violated. ChainMiner's
	//					action may be cancelled and replaced with the action
	//					[do_nothing()].
	
	const bool sack_full();

	// Purpose:			Returns whether [cm_sack] == [cm_sack_max].
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	const bool sack_empty();

	// Purpose:			Returns whether [cm_sack] == [0].
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	const short sack_space();

	// Purpose:			Returns space remaining in [cm_sack].
	// Preconditions:	None.
	// Returns:			[short].
	// Side Effects:	None.
	// Errors:			None.

	const bool tired();

	// Purpose:			Returns whether [cm_endurance] <= [0].
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	const bool recovered();

	// Purpose:			Returns whether [cm_endurance] == [12].
	// Preconditions:	None.
	// Returns:			[bool].
	// Side Effects:	None.
	// Errors:			None.

	void tire();

	// Purpose:			Reduces [cm_endurance] by 1. Minimum is [0].
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	void recover();

	// Purpose:			Increases [cm_endurance] by 1. Maximum is [12].
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	void set_facing(const short x, const short y);

	// Purpose:			Sets [cm_facing] according to [x] and [y].
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	const bool facing_is_space(short &x, short &y);

	// Purpose:			If ChainMiner is facing a space according to
	//					[cm_facing], [x] and [y] are loaded with the
	//					coordinates of that adjacent space. Otherwise
	//					a random adjacent space is loaded. Otherwise
	//					returns [false]
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.
	
	// *** PRIVATE MEMBER VARIABLES ***

	short cm_sack;			// a sack for carrying things
	short cm_sack_max;		// max capacity of sack
	short cm_scoop;			// max amount Miner can scoop in one turn
	short cm_endurance;		// getting tired
	short cm_facing;		// index over MOVES[] that records a heading
	
};

#endif