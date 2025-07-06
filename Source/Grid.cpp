//	Filename:		Grid.cpp
//	Version:		Final
//	Author:			Paul Tinsley (pmbtin)
//	Date:			27 February, 1999
//	Platform:		Visual C++ 5.00

//	Purpose:		See Grid.h.

#include "stdafx.h"
#include "Grid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	*** CONSTRUCTORS ***

Grid::Grid()  : g_SIZE(40), g_state(false)

{

	g_list.clear();
	g_lookup.clear();

}

Grid::Grid(const short s): g_SIZE(s), g_state(true)

{
		
	g_list.clear();
	g_lookup.clear();

	if(g_SIZE > MAX_DIMENSION || g_SIZE < MIN_DIMENSION)

	{
		
		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Grid::Grid(s), a size [s] of " << g_SIZE;
		err << " is out of range.\nThe Grid cannot be set!\n";
		err << "FORCED EXIT!\n";
		err.close();
		exit(1);

	}
		
	const short limit = (g_SIZE * g_SIZE);

	// allocate vector memory
	g_list.reserve(limit);

	// tidy up the vector to save memory
	g_list.resize(limit);

	// set all elements to spaces
	wipe(0);

	// create a lookup table
	create_lookup();	
	
}

Grid::Grid(const Grid &g)

{

	g_list = g.g_list;
	g_SIZE = g.g_SIZE;
	g_state = g.g_state;
	g_lookup = g.g_lookup;

}

//	*** OPERATORS ***

Grid & Grid::operator =(const Grid &g)

{

	g_list = g.g_list;
	g_SIZE = g.g_SIZE;
	g_state = g.g_state;
	g_lookup = g.g_lookup;

	return(*this);

}

const bool Grid::operator ==(const Grid &g)

{

	return(g_list == g.g_list);

}

//	*** PUBLIC FUNCTIONS ***

void Grid::put(const short x, const short y, const short v)

{

	if(!g_state)

	{

		return;

	}
	
	if(!check(x,y))

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Grid::put(x,y,v), [x] or [y] is out of range.\n";
		err << "The put operation of " << v << " to (" << x << "," << y << ")\n";
		err << "failed for this Grid of dimension " << g_SIZE << ".\n";
		err.close();
		g_state = false;
		return;

	}

	if(v < MIN_VALUE || v > MAX_VALUE)

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Grid::put(x,y,v), [v] is out of range.\n";
		err << "The put operation of " << v << " to (" << x << "," << y << ")\n";
		err << "failed for this Grid of dimension " << g_SIZE << ".\n";
		err.close();
		g_state = false;
		return;

	}

	// map cartesian coordinates to contiguous and unique list coordinates
	g_list[x + g_lookup[y]] = v;

}

void Grid::put_f(const short x, const short y, const short v)

{

	g_list[x + g_lookup[y]] = v;

}

const short Grid::get(const short x, const short y)

{

	if(!g_state)

	{

		return(0);

	}
	
	if(!check(x,y))

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Grid::get(x,y), [x] or [y] is out of range.\n";
		err << "The get operation from coordinates (" << x << "," << y << ")\n";
		err << "failed for this Grid of dimension " << g_SIZE << ".\n";
		err.close();
		g_state = false;
		return(0);

	}

	return(g_list[x + g_lookup[y]]);
	
}

const short Grid::get_f(const short x, const short y)

{

	return(g_list[x + g_lookup[y]]);
	
}

const bool Grid::get_state()

{

	return(g_state);

}

void Grid::set_state(const bool s)

{

	g_state = s;

}

const short Grid::get_dim()

{

	return(g_SIZE);

}

void Grid::wipe(const short v)

{
	
	if(!g_state)

	{

		return;

	}

	if(v < MIN_VALUE || v > MAX_VALUE)

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Grid::wipe(v), [v] is out of range.\n";
		err << "The wipe operation has failed.\n";
		err.close();
		g_state = false;
		return;

	}

	// this is an STL container algorithm
	fill(g_list.begin(),g_list.end(),v);

}

void Grid::replace_all_instances(const short v, const short r)

{
	
	if(!g_state)

	{

		return;

	}

	if(v < MIN_VALUE || v > MAX_VALUE || r < MIN_VALUE || r > MAX_VALUE)

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Grid::replace_all_instances(v,r),\n";
		err << "[v] or [r] is out of range. The replace operation has failed.\n";
		err.close();
		g_state = false;
		return;

	}

	// an STL container algorithm
	replace(g_list.begin(),g_list.end(),v,r);

}

void Grid::replace_all_non_zero_instances(const short r)

{
	
	if(!g_state)

	{

		return;

	}

	if(r < MIN_VALUE || r > MAX_VALUE)

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Grid::replace_all_non_zero_instances(r),\n";
		err << "[r] is out of range. The replace operation has failed.\n";
		err.close();
		g_state = false;
		return;

	}

	// an STL container algorithm
	replace_if(g_list.begin(),g_list.end(),is_greater_zero(),r);

}

void Grid::expire_moving()

{
	
	// an STL container algorithm
	replace_if(g_list.begin(),g_list.end(),is_moving_object(),SPACE);

}

const short Grid::count_all_instances(const short v)

{
	
	if(!g_state)

	{

		return(0);

	}

	if(v < MIN_VALUE || v > MAX_VALUE)

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Grid::count_all_instances(v), [v]\n";
		err << "is out of range. The count operation has failed.\n";
		err.close();
		g_state = false;
		return(0);

	}

	// an STL container algorithm
	return(short(count(g_list.begin(),g_list.end(),v)));
	
}

const bool Grid::find_instance(const short v)

{

	if(!g_state)

	{

		return(0);

	}

	if(v < MIN_VALUE || v > MAX_VALUE)

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Grid::find_instance(v), [v]\n";
		err << "is out of range. The find operation has failed.\n";
		err.close();
		g_state = false;
		return(0);

	}

	// an STL container algorithm
	SHORTVECTOR_IT f = find(g_list.begin(),g_list.end(),v);

	return(f != g_list.end());


}

const void Grid::output(ofstream &out)

{
	
	if(!g_state)

	{

		return;

	}

	if(out.fail())

	{


		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Grid::output(out), stream failure!\n";
		err << "The data could not be output.\n";
		err.close();
		g_state = false;
		return;

	}
		
	short count;
	
	for(count = 0 ; count < (g_SIZE * g_SIZE) ; count++)

	{
		
		if((count % g_SIZE) == 0)

		{

			out << endl;

		}
		
		out << g_list[count] << " ";

	}

}

void Grid::input(ifstream &in)

{
	
	if(!g_state)

	{

		return;

	}
		
	if(in.fail())

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Grid::set_map(in), stream failure!\n";
		err << "The data from the file could not be loaded.\n";
		err.close();
		g_state = false;
		return;

	}
	
	SHORTVECTOR_IT locator;
	short value;
	
	for(locator = g_list.begin() ; locator != g_list.end() ; ++locator)

	{
		
		in >> value;

		if(in.fail() || in.eof())

		{

			ofstream err("errlog.txt", ios::app);
			err << "\n\nERROR, Grid::set_map(in), stream failure!\n";
			err << "The data from the file could not be loaded correctly.\n";
			err.close();
			g_state = false;
			return;

		}
	
		*locator = value;
	
	}

}

const bool Grid::check(const short x, const short y)

{
	
	return((x < g_SIZE) && (x >= 0) && (y < g_SIZE) && (y >= 0));
		
}

void Grid::metamorphose(const short s)

{

	if(s > MAX_DIMENSION || s < MIN_DIMENSION)

	{

		ofstream err("errlog.txt", ios::app);
		err << "\n\nERROR, Grid::metamorphose(s), [s] is out of range.\n";
		err << "The metamorphose of this Grid has failed.\n";
		err.close();
		g_state = false;
		return;
		
	}

	// erase old
	g_list.clear();
	
	// set new dimension
	g_SIZE = s;

	// reset error state
	g_state = true;

	// calculate vector limit
	const short limit = (g_SIZE * g_SIZE);

	// allocate vector memory
	g_list.reserve(limit);

	// tidy up the vector to save memory
	g_list.resize(limit);

	// set all elements to zero
	wipe(0);

	// create a lookup table
	create_lookup();	
	
}

//	*** PRIVATE FUNCTIONS ***

void Grid::create_lookup()

{

	g_lookup.clear();

	for(short y = 0 ; y < g_SIZE ; y++)

	{

		g_lookup.push_back(y * g_SIZE);

	}

	g_lookup.resize(g_SIZE);

}