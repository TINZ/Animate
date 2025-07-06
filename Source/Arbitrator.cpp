//	Filename:		Arbitrator.cpp
//	Version:		Final
//	Author:			Paul Tinsley (pmbtin)
//	Date:			26 February, 1999
//	Platform:		Visual C++ 5.00

//	Purpose:		See Arbitrator.h.

#include "stdafx.h"
#include "Arbitrator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	*** CONSTRUCTORS ***

Arbitrator::Arbitrator() : a_fail_value(0)

{

	a_intents.clear();
	
}

Arbitrator::Arbitrator(const INTENT_LIST &i, const short fail): a_fail_value(fail)

{

	a_intents = i;
	a_primary = i;
	
}

Arbitrator::Arbitrator(const Arbitrator &x)

{

	a_intents = x.a_intents;
	a_primary = x.a_primary;
	a_fail_value = x.a_fail_value;

}

//	*** OPERATORS ***

Arbitrator & Arbitrator::operator =(const Arbitrator &x)

{

	a_intents = x.a_intents;
	a_primary = x.a_primary;
	a_fail_value = x.a_fail_value;
	return *this;

}

//	*** PUBLIC FUNCTIONS ***

void Arbitrator::set_fail(const short f)

{

	a_fail_value = f;

}

void Arbitrator::set_initial_intents(INTENT_LIST &i)

{

	a_intents = i;
	a_primary = i;

}

void Arbitrator::arbitrate(INTENT_LIST &i)

{

	// first update priorities
	compare_intents(i);
	
	INTENT_LIST_IT f;
	INTENT_LIST_IT f1;
	Intent match;
	INTENT_LIST found;
	INTENT_LIST result;
	INTENT_LIST original;
	
	// make action classes for arbitration
	set_classes(i);

	short count,clobber,winner;
	
	// now look for conflicts
	while(!i.empty())

	{

		f = i.begin();
		match = *f;

		f1 = f;
		
		// look for matches on basis of action and key
		while(f1 != i.end())

		{

			if(*f1 == match)

			{

				found.push_back(*f1);
				i.erase(f1);
				f1 = i.begin();
				
			}

			else

			{

				f1++;

			}
			
		};

		// sort the list of matches
		sort(found.begin(),found.end(),compare_intent_priorities());
		
		// probably have a list of matched items so deal with it
		if(found.size() >= 2)

		{
			
			f1 = found.begin();
			
			if((f1 -> get_priority()) > ((f1+1) -> get_priority()))
				
			{

				// winner loses his priority
				f1 -> reset_priority();
				f1++;

				while(f1 != found.end())

				{	// set all of the losers

					f1 -> set_action(a_fail_value);
					f1 -> inc_priority();
					f1++;

				};

			}

			else

			{

				// have to count clobbers, pick winner and set rest to NOTHING
				f1 = found.begin();
				match = *f1;
				clobber = 0;

				while((f1 != found.end()) && (f1 -> get_priority() == match.get_priority()))

				{

					clobber++;
					f1++;

				};
							
				winner = rand() % clobber;
				f1 = found.begin();
				count = 0;

				while(f1 != found.end())

				{	// go right to end cos there may be lower priorities

					if(count != winner)

					{

						f1 -> set_action(a_fail_value);
						f1 -> inc_priority();

					}

					else

					{

						// winner loses his priority
						f1 -> reset_priority();

					}

					f1++;
					count++;

				};

			}

		}

		else

		{

			// there must only be one - he wins and loses priority
			f1 = found.begin();
			f1 -> reset_priority();

		}
			
		// copy findings to result list
		f1 = found.begin();

		while(f1 != found.end())

		{

			result.push_back(*f1);
			f1++;

		};

		found.clear();

		f++;

	};

	// put back actual actions
	remove_classes(result);
	// give result to caller
	i = a_intents;

}

//	*** PRIVATE FUNCTIONS ***

void Arbitrator::compare_intents(INTENT_LIST &i)

{

	short lim = a_intents.size();
	short c;

	// sort both lists by agent's name - then we can index them
	sort(a_intents.begin(), a_intents.end(), compare_intent_names());
	sort(i.begin(), i.end(), compare_intent_names());

	for(c = 0 ; c < lim; c++)

	{

		if((a_intents[c].get_action() != i[c].get_action()) &&
			(a_intents[c].get_key() != i[c].get_key()))

		{
			
							
			i[c].reset_priority();
			

		}

	}

	// get copy or these original intents
	a_primary = i;

}

void Arbitrator::set_classes(INTENT_LIST &i)

{

	INTENT_LIST_IT it;
	
	for(it = i.begin() ; it != i.end() ; ++it)

	{
		
		switch(it -> get_action())

		{

		case MOVE:

			it -> set_action(C_INHABIT);
			break;

		case GRAB:

			it -> set_action(C_INTERACT);
			break;

		case DROP:

			it -> set_action(C_INHABIT);
			break;

		case POUNCE:

			it -> set_action(C_INTERACT);
			break;

		case JUMP:

			it -> set_action(C_INHABIT);
			break;
		
		default:

			break;

		};

	}

}

void Arbitrator::remove_classes(INTENT_LIST &i)

{

	// sort intents
	sort(i.begin(),i.end(),compare_intent_names());
	
	// run through and set fails

	short count = 0;

	while(count < a_primary.size())

	{

		if(i[count].get_action() == a_fail_value)

		{

			a_primary[count].set_action(a_fail_value);

		}

		count++;

	};

	// copy to a_intents for matching next turn
	a_intents = a_primary;

}