//	Filename:		Arbitrator.h
//	Version:		Final
//	Author:			Paul Tinsley (pmbtin)
//	Date:			26 February, 1999
//	Platform:		Visual C++ 5.00

//	Symbology:		Numbers, functions and data variables are enclosed in
//					square parentheses "[]". This is to remove any
//					ambiguity within the text of comments. All private data
//					member variables are prefixed by "a_".

//	Purpose:		Generic arbitration. The arbitrator simply matches all agents
//					that wish to perform the same action at the same location
//					and selects a "winner" via priority or randomisation.

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

#ifndef __ARBITRATOR_H
#define __ARBITRATOR_H

#include "Intent.h"			// agent intentions
#include "Environment.h"	// for action enumerations
#include <vector>			// for containers of [Intent]
#include <algorithm>		// sorting containers

using namespace std;

typedef vector<Intent> INTENT_LIST;					// list of [Intent]'s
typedef INTENT_LIST :: iterator INTENT_LIST_IT;

class Arbitrator

{

	public:

	//	*** CONSTRUCTORS ***

	Arbitrator();

	// Purpose:			Default constructor.
	// Preconditions:	None.
	// Returns:			[Arbitrator] object.
	// Side Effects:	None.
	// Errors:			None.

	Arbitrator(const INTENT_LIST &i, const short fail);

	// Purpose:			Constructor. [a_intents] gets [i], [a_fail_value] gets [fail].
	// Preconditions:	None.
	// Returns:			[Arbitrator] object.
	// Side Effects:	None.
	// Errors:			None.
	
	Arbitrator(const Arbitrator &x);

	// Purpose:			Copy Constructor.
	// Preconditions:	None.
	// Returns:			[Arbitrator] object.
	// Side Effects:	None.
	// Errors:			None.
	
	//	*** OPERATORS ***

	Arbitrator & operator =(const Arbitrator &x);

	// Purpose:			Destructive assignment operator.
	// Preconditions:	None.
	// Returns:			[Arbitrator] object.
	// Side Effects:	None.
	// Errors:			None.
		
	//	*** PUBLIC FUNCTION PROTOTYPES ***

	void set_fail(const short f);

	// Purpose:			[a_fail_value] gets [fail]. This is the action value that
	//					the	arbitrator will record in an [Intent] that fails to
	//					"win" in arbitration. This should normally be [NOTHING].
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.
	
	void set_initial_intents(INTENT_LIST &i);

	// Purpose:			[a_intents] gets [i]. The arbitrator needs a copy of the
	//					agents initial intents to maintain the structure of the
	//					arbitration system. The intentions for the last turn are
	//					always matched against those of the current turn in order
	//					to calculate priorities.
	// Preconditions:	Done before first [arbitrate(INTENT_LIST &i)] invocation.
	//					Thereafter, never again unless restarting the experiment.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.
		
	void arbitrate(INTENT_LIST &i);

	// Purpose:			Arbitrate over [i]. Then copy [i] to [a_intents].
	// Preconditions:	[a_intents] represents the last turns arbitrated
	//					actions.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.
		
	private:

	//	*** PRIVATE DATA ***

	INTENT_LIST a_intents;		// copy of last intents
	INTENT_LIST a_primary;		// agents intents without classification
	short a_fail_value;			// value to load into intents that lose in arbitration

	//	*** PRIVATE FUNCTIONS ***

	void compare_intents(INTENT_LIST &i);

	// Purpose:			Increase priorities for all intents in [i] that match same action
	//					and key in [a_intents]. Sets non-matching elements to zero
	//					priority as the agent has decided to perform a different action.
	// Preconditions:	None.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	void set_classes(INTENT_LIST &i);

	// Purpose:			Maps all actions in [i] to the correct action class.
	// Preconditions:	[i] has not been arbitrated.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.

	void remove_classes(INTENT_LIST &i);

	// Purpose:			Removes the action class and replaces the original
	//					action if the action is not [NOTHING].
	// Preconditions:	[i] has been arbitrated.
	// Returns:			None.
	// Side Effects:	None.
	// Errors:			None.
		
};

#endif