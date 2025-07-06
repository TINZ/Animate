//	Filename:		DataStructures.h
//	Version:		Final
//	Author:			Paul Tinsley (pmbtin)
//	Date:			26 February, 1999
//	Platform:		Visual C++ 5.00

//	Purpose:		Data structures used in various areas of the system.

#ifndef __DATASTRUCTURES_H
#define __DATASTRUCTURES_H

#include <vector>			// container type

using namespace std;

// The following simple class is used in calculating minimal paths amongst
// others. It's very handy to have a triple.

class triple
{
public:
	triple() : x(0), y(0), z(0){};
	triple(const short a, const short b, const short c) : x(a), y(b), z(c) {};
	triple & operator =(const triple &a)
	{x = a.x; y = a.y; z = a.z; return *this;};
	const bool friend operator ==(const triple &a, const triple &b)
	{return(a.x == b.x && a.y == b.y && a.z == b.z);};
	const bool friend operator <(const triple &a, const triple &b)
	{return(a.z < b.z);};
	const void get(short &a, short &b, short &c)
	{a = x; b = y; c = z;};
	void put(const short a, const short b, const short c)
	{x = a; y = b; z = c;};
private:
	short x;
	short y;
	short z;
};

typedef vector<triple> PATH;	// a collection of triples, useful in path
typedef PATH::iterator PATH_IT;	// building

// this simple class is used in scripts

class chunk
{
public:
	chunk() : c1(0), c2(0), c3(0), c4(0), c5(0), c6(0), c7(0), c8(0), c9(0){};
	chunk(const short a, const short b, const short c, const short d,
			const short e, const short f, const short g, const short h,
			const short i)
			: c1(a), c2(b), c3(c), c4(d), c5(e), c6(f), c7(g), c8(h), c9(i){};
	chunk & operator =(const chunk &a)
	{c1 = a.c1; c2 = a.c2; c3 = a.c3; c4 = a.c4;
		c5 = a.c5; c6 = a.c6; c7 = a.c7; c8 = a.c8; c9 = a.c9; return *this;};
	const bool friend operator ==(const chunk &a, const chunk &b)
	{return(a.c1 == b.c1 && a.c2 == b.c2 && a.c3 == b.c3 && a.c4 == b.c4
			&& a.c5 == b.c5 && a.c6 == b.c6 && a.c7 == b.c7 && a.c8 == b.c8
			&& a.c9 == b.c9);};
	const bool friend operator <(const chunk &a, const chunk &b)
	{return(a.c1 < b.c1);};

	//	*** GETTERS, PUTTERS & TRANSFORMERS ***
	
	// get all data
	const void get(short &a, short &b, short &c, short &d, short &e, short &f,
					short &g, short &h, short &i)
	{a = c1; b = c2; c = c3; d = c4; e = c5; f = c6; g = c7; h = c8; i = c9;};
	
	// put all data
	void put(const short a, const short b, const short c, const short d,
				const short e, const short f, const short g, const short h,
				const short i)
	{c1 = a; c2 = b; c3 = c; c4 = d; c5 = e; c6 = f; c7 = g; c8 = h; c9 = i;};
	
	// get data for trails
	const void get_trails(short &a, short &b, short &c, short &d, short &e,
							short &h, short &i)
	{a = c1; b = c2; c = c3; d = c4; e = c5; h = c8; i = c9;};
	
	// get data for tagging
	const void get_tagging(short &b, short &c, short &d, short &e, short &f,
					short &h, short &i)
	{b = c2; c = c3; d = c4; e = c5; f = c6; h = c8; i = c9;};
	
	// get data for scenario animation
	const void get_anim(short &a, short &b, short &c, short &d)
	{a = c2; b = c4; c = c5; d = c7;};

	// get data for paths
	const void get_paths(short &a, short &b, short &d, short &e)
	{a = c1; b = c2; d = c4; e = c5;};

	// get data for prey killed
	const void get_agent(short &a, short &b, short &c)
	{a = c1; b = c2; c = c3;};

	// get data for predator stomachs
	const void get_quantity(short &a, short &b, short &g)
	{a = c1; b = c2; g = c7;};

	// get data for agent locations
	const void get_loc(short &a, short &b, short &c, short &d, short &e)
	{a = c1; b = c2; c = c3; d = c4; e = c5;};

	// get frame count for this info field
	const void get_frames(short &b)
	{b = c2;};

	// get info field
	const void get_info(short &a)
	{a = c1;};

	// adjust coords for screen anim
	void screen_coords()
	{c4*=10;c5*=10;c8*=10;c9*=10;};
	
private:
	short c1;		// info field flag for dynamic frame size data
	short c2;		// object type or frame count if an info field
	short c3;		// agent id
	short c4;		// agent x-coord
	short c5;		// agent y-coord
	short c6;		// agent action
	short c7;		// object quantity possessed
	short c8;		// agent target x-coord
	short c9;		// agent target y-coord
	
};

typedef vector<chunk> SCRIPT;			// script for animation
typedef SCRIPT :: iterator SCRIPT_IT;

// to hold scenario info

struct SCENARIO_DATA

{

	int total_agents;		// total agents in scenario
	short mining_agents;	// mining agents
	short predator_agents;	// predator agents
	short prey_agents;		// prey agents
	short miner_vis;		// miner vision range
	short predator_vis;		// predator vision range
	short prey_vis;			// prey vision range
	short miner_grab;		// miner grab capactity
	short miner_sack;		// miner sack capacity	
	short pred_stom_m;		// predator max stomach capacity
	short pred_stom_i;		// predator init stomach capacity
	short turns;			// turns in this scenario
	int scenario_type;		// type of scenario run
	bool exploring;			// whether agents had to explore map

	// have not included amount of scenarios run.

};

typedef vector<long> FRAMES;			// script for animation
typedef FRAMES :: iterator FRAMES_IT;

#endif