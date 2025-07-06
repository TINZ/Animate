//	Filename:		Environment.cpp
//	Version:		Final
//	Author:			Paul Tinsley (pmbtin)
//	Date:			28 February, 1999
//	Platform:		Visual C++ 5.00

//	Purpose:		See Environment.h for details.

#include "stdafx.h"
#include "Environment.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	*** OPERATORS ***

Environment & Environment::operator =(const Environment &e)

{

	e_object = e.e_object;
	e_value = e.e_value;
		
	return *this;

}

//	*** PUBLIC FUNCTIONS ***

void Environment::input_objects(ifstream &in)

{
	
	e_object.input(in);
	e_value.input(in);
	
}

const void Environment::output_objects(ofstream &out)

{
	
	e_object.output(out);
	out << endl;
	e_value.output(out);
	
}

void Environment::put_object(const short x, const short y, const short i, const short q)

{
	
	e_object.put(x,y,i);
	e_value.put(x,y,q);

}

void Environment::put_object_f(const short x, const short y, const short i, const short q)

{

	e_object.put_f(x,y,i);
	e_value.put_f(x,y,q);

}

const short Environment::get_object(const short x, const short y)

{

	return(e_object.get(x,y));
	
}

const short Environment::get_object_f(const short x, const short y)

{

	return(e_object.get_f(x,y));

}

const void Environment::get_object(const short x, const short y, short &i, short &q)

{

	i = e_object.get(x,y);
	q = e_value.get(x,y);
	
}

const void Environment::get_object_f(const short x, const short y, short &i, short &q)

{

	i = e_object.get_f(x,y);
	q = e_value.get_f(x,y);

}

void Environment::put_quantity(const short x, const short y, const short q)

{
	
	e_value.put(x,y,q);

}

void Environment::put_quantity_f(const short x, const short y, const short q)

{
	
	e_value.put_f(x,y,q);

}

const short Environment::get_quantity(const short x, const short y)

{

	return(e_value.get(x,y));

}

const short Environment::get_quantity_f(const short x, const short y)

{

	return(e_value.get_f(x,y));

}

short Environment::take_quantity(const short x, const short y, const short a)

{

	if(e_object.get(x,y) == SPACE)

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Environment::take_quantity(x,y,a), An object does.\n";
		err << "not exist at this location. Get operation failed.\n";
		err.close();
		return(0);

	}
	
	short q = e_value.get(x,y);

	if(q <= a)

	{	// all used up so adjust environment and record destroyed object

		e_object.put(x,y,SPACE);
		e_value.put(x,y,SPACE);
		return(q);

	}

	else

	{

		q -= a;
		e_value.put(x,y,q);
		return(a);

	}

}

short Environment::take_quantity_f(const short x, const short y, const short a)

{
	
	short q = e_value.get_f(x,y);

	if(q <= a)

	{	// all used up so adjust environment and record destroyed object

		e_object.put_f(x,y,SPACE);
		e_value.put_f(x,y,SPACE);
		return(q);

	}

	else

	{

		q -= a;
		e_value.put_f(x,y,q);
		return(a);

	}

}

bool Environment::add_quantity(const short x, const short y, const short i, const short a)

{

	short t = e_object.get(x,y);
	short q = e_value.get(x,y);

	if(t == i || t == SPACE || t == HOME || t == ORE || t == CARCASS)

	{

		if((q+a) <= MAX_VALUE)

		{

			e_value.put(x,y,q+a);

			if(t == SPACE)

			{

				e_object.put(x,y,i);

			}

			return(true);

		}

		else

		{

			return(false);

		}

	}

	else

	{

		return(false);

	}

}

bool Environment::add_quantity_f(const short x, const short y, const short i, const short a)

{

	short t = e_object.get_f(x,y);
	short q = e_value.get_f(x,y);

	if((q+a) <= MAX_VALUE)

	{

		e_value.put_f(x,y,q+a);

		if(t == SPACE)

		{

			e_object.put_f(x,y,i);

		}

		return(true);

	}

	else

	{

		return(false);

	}
	
}

void Environment::rand_all_quantities(const short o, const short min, const short max)

{

	if(o < MIN_VALUE || o > MAX_VALUE || min < MIN_VALUE || min > MAX_VALUE ||
		max < MIN_VALUE || max > MAX_VALUE)

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Environment::rand_all_quantities(o,min,max), An\n";
		err << "argument is out of range. Randomisation of all quantities failed.\n";
		err.close();
		return;

	}

	if((max - min) <= 0)

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Environment::rand_all_quantities(o,min,max), [max]\n";
		err << "must be greater than [min]. Randomisation of all quantities failed.\n";
		err.close();
		return;

	}

	short rand_e = max - min;
	short c1,c2;
	short dim = e_object.get_dim();

	for(c1 = 0 ; c1 < dim ; c1++)

	{

		for(c2 = 0 ; c2 < dim ; c2++)

		{

			if(e_object.get_f(c1,c2) == o)

			{

				e_value.put_f(c1,c2,(rand() % rand_e) + min);

			}

		}

	}

}

void Environment::set_all_quantities(const short o, const short v)

{

	if(o < MIN_VALUE || o > MAX_VALUE || v < MIN_VALUE || v > MAX_VALUE)

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Environment::set_all_quantities(o,v), An\n";
		err << "argument is out of range. Setting of all quantities failed.\n";
		err.close();
		return;

	}

	short c1,c2;
	short dim = e_object.get_dim();

	for(c1 = 0 ; c1 < dim ; c1++)

	{

		for(c2 = 0 ; c2 < dim ; c2++)

		{

			if(e_object.get_f(c1,c2) == o)

			{

				e_value.put_f(c1,c2,v);

			}

		}

	}

}

void Environment::metamorphose(const short s)

{

	e_object.metamorphose(s);
	e_value.metamorphose(s);

}

void Environment::clear_objects(const short o)

{
	
	set_all_quantities(o,0);
	e_object.replace_all_instances(o,0);

}

void Environment::clear_all()

{

	e_object.wipe(0);
	e_value.wipe(0);

}

const short Environment::get_dim()

{

	return(e_object.get_dim());

}

const bool Environment::check_coord(const short x, const short y)

{

	return(e_object.check(x,y));

}

void Environment::get_all_objects(Grid &g)

{

	g = e_object;

}

const bool Environment::get_state()

{

	return(e_object.get_state() && e_value.get_state());

}

const bool Environment::contains_object(const short v)

{

	return(e_object.find_instance(v));

}