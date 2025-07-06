//	Filename:		Intent.cpp
//	Version:		Final
//	Author:			Paul Tinsley (pmbtin)
//	Date:			8 February, 1999
//	Platform:		Visual C++ 5.00

//	Purpose:		See Intent.h

#include "stdafx.h"
#include "Intent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	*** CONSTRUCTORS ***

Intent::Intent(const Intent &i)

{
	
	i_name = i.i_name;
	i_action = i.i_action;
	i_priority = i.i_priority;
	i_x = i.i_x;
	i_y = i.i_y;
	i_key = i.i_key;
	i_const = i.i_const;

}

Intent::Intent(short n, short a, short p, short x, short y, short c)
: i_name(n), i_action(a), i_priority(p), i_x(x), i_y(y), i_const(c)

{

	if(p < 0 || p > MAX_PRIORITY)

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Intent::Intent(n,a,p,x,y,c), [p] is out\n";
		err << "of range. FORCED EXIT!\n";
		err.close();
		exit(1);

	}
	
	if(c < MIN_DIMENSION || c > MAX_DIMENSION)

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Intent::Intent(n,a,p,x,y,c), [c] is out\n";
		err << "of range. FORCED EXIT!\n";
		err.close();
		exit(1);

	}
	
	set_key();

}

//	*** OPERATORS ***

Intent & Intent::operator =(const Intent &i)

{
	
	i_name = i.i_name;
	i_action = i.i_action;
	i_priority = i.i_priority;
	i_x = i.i_x;
	i_y = i.i_y;
	i_key = i.i_key;
	i_const = i.i_const;

	return(*this);

}

//	*** PUBLIC FUNCTIONS ***

const void Intent::get(short &n, short &a, short &p, short &x, short &y)

{

	n = i_name;
	a = i_action;
	p = i_priority;
	x = i_x;
	y = i_y;

}

const void Intent::get(short &a, short &x, short &y)

{

	a = i_action;
	x = i_x;
	y = i_y;

}

void Intent::reset_priority()

{

	i_priority = 0;

}

const void Intent::get(short &x, short &y)

{

	x = i_x;
	y = i_y;

}

const short Intent::get_name()

{

	return(i_name);

}

const void Intent::get_action(short &a, short &p, short &k)

{

	a = i_action;
	p = i_priority;
	k = i_key;

}

const short Intent::get_action()

{

	return(i_action);

}

const short Intent::get_priority()

{

	return(i_priority);

}

const short Intent::get_key()

{

	return(i_key);

}

void Intent::put(const short n, const short a, const short p, const short x,
				 const short y, const short c)

{

	i_name = n;
	i_action = a;
	i_priority = p;
	i_x = x;
	i_y = y;
	i_const = c;
	set_key();

}

void Intent::put(const short a, const short x, const short y)

{

	i_action = a;
	i_x = x;
	i_y = y;
	set_key();
	
}

void Intent::inc_priority()

{

	i_priority++;

	if(i_priority > MAX_PRIORITY)

	{

		ofstream err("errlog.txt", ios::app);
		err << "\nCAUTION, Intent::inc_priority(), i_priority exceeding ";
		err << MAX_PRIORITY << " .. set to 0.\n";
		err.close();
		i_priority = 0;

	}

}

void Intent::set_name(const short n)

{

	i_name = n;

}

void Intent::set_action(const short a)

{

	i_action = a;

}

//	*** PRIVATE FUNCTIONS ***

void Intent::set_key()

{

	i_key = (i_x + (i_y * i_const));

	if(i_key > MAX_KEY)

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Intent::set_key(), coordinates exceed maximum range.\n";
		err << "FORCED EXIT!\n";
		err.close();
		exit(1);

	}

}