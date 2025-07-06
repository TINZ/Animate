//	Filename:		Grid.h
//	Version:		Final
//	Author:			Paul Tinsley (pmbtin)
//	Date:			27 February, 1999
//	Platform:		Visual C++ 5.00

//	Symbology:		Numbers, functions and data variables are enclosed in
//					square parentheses "[]". This is to remove any
//					ambiguity within the text of comments. All private data
//					member variables are prefixed by "g_". Any function with
//					the suffix "_f" is a faster version of that function as
//					there is no range / error checking.

//	Errors:			All error messages appended to "errlog.txt".

//	Purpose:		This class implements a two-dimensional grid with
//					square dimensions that may be accessed by cartesian
//					parameters using an implementation of the STL [vector]
//					container. Any n*n grid of [short] types may be defined
//					within the range [10]*[10] up to a max size of [40]*[40].
//					The origin of the grid is ([0],[0]) up to a maximum
//					reference of ([s]-[1],[s]-[1]), [s] being the dimension
//					of the grid. The origin is perceived as starting at the
//					top left and writing in rows of [s] down the "screen".

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

#ifndef __GRID_H
#define __GRID_H

#include <vector>				// to contain [Grid] elements
#include <fstream>				// output / input / from files
#include <stddef.h>				// for program error exit
#include <algorithm>			// generic container functions

//	*** TYPE DEFINITIONS / GLOBALS / COMPILER FLAGS ***

using namespace std;			// standard namespace directive

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.

#pragma warning(disable:4786)
					
typedef vector<short> SHORTVECTOR;				// the vector type
typedef SHORTVECTOR :: iterator SHORTVECTOR_IT;	// iterator over SHORTVECTOR
const short MAX_DIMENSION = 40;					// largest Grid dimension
const short MIN_DIMENSION = 10;					// smallest Grid dimension
const short MAX_VALUE = 32700;					// largest Grid location value
const short MIN_VALUE = -32700;					// smallest Grid location value	

//	*** OBJECT / ACTION ENUMERATIONS ***

/*	The following enumerations provide a symbology to the programmer for types
	of objects, actions and action classes. Further details occur in the report.
*/
enum {SPACE,OBSTACLE,MINER,PREDATOR,PREY,CARCASS,MINERAL,ORE,HOME,UNKNOWN,MOVE,
		NOTHING,GRAB,DROP,POUNCE,JUMP,ASTART,C_INHABIT,C_INTERACT};

//	NOTES:	Order is important. All agents must fall after MINER and before
//			MINERAL. All non-agent and non-space and non-obstacle items must
//			fall after MINERAL.

//	*** CLASS DEFINITION ***

class Grid

{

	public:

		//	*** CONSTRUCTORS ***

		Grid();

		// Purpose:			Default constructor.
		// Preconditions:	None.
		// Returns:			A [Grid] instance.
		// Side Effects:	The Grid is not fully constructed. Note
		//					that the Grid dimension may be redefined
		//					and the Grid rebuilt by using the member
		//					function [metamorphose(const short s)].
		// Errors:			None.

		Grid(const short s);
		
		// Purpose:			Creates a [Grid] instance based on dimension [s]
		//					and	initialises all contained values to [0].
		// Preconditions:	[s] >= [MIN_DIMENSION] && [s] <= [MAX_DIMENSION].
		// Returns:			A [Grid] instance.
		// Side Effects:	None.
		// Errors:			[errlog] error message if precondition violation.
		//					Program then terminates.

		//	*** COPY CONSTRUCTOR ***

		Grid(const Grid &g);

		// Purpose:			Creates a copy of a [Grid] instance based on
		//					the [Grid] parameter [g].
		// Preconditions:	None.
		// Returns:			A [Grid] instance.
		// Side Effects:	None.
		// Errors:			None.

		//	*** OPERATORS ***

		Grid & operator =(const Grid &g);

		// Purpose:			Destructively assigns [g] to the current
		//					context.
		// Preconditions:	None.
		// Returns:			None.
		// Side Effects:	Destructive assignment.
		// Errors:			None.

		const bool operator ==(const Grid &g);

		// Purpose:			Deep equality operator.
		// Preconditions:	None.
		// Returns:			[bool] [true]/[false].
		// Side Effects:	None.
		// Errors:			None.
		
		//	*** PUBLIC FUNCTION PROTOTYPES ***

		void put(const short x, const short y, const short v);
		void put_f(const short x, const short y, const short v);

		// Purpose:			Sets element at coordinate ([x],[y]) to
		//					value specified by [v].
		// Preconditions:	If ![g_state], function exits without putting.
		//					[x] < [g_SIZE] && [x] >= [0] && [y] < [g_SIZE]
		//					&& [y] >= [0]. [v] >= [MIN_VALUE] && [v] <=
		//					[MAX_VALUE].
		// Returns:			None.
		// Side Effects:	None.
		// Errors:			[errlog] error message if precondition violated.
		//					No action is performed. [g_state] = [false].
	
		const short get(const short x, const short y);
		const short get_f(const short x, const short y);

		// Purpose:			Returns value held at coordinate ([x],[y]).
		// Preconditions:	If ![g_state], function exits without getting.
		//					[x] < [g_SIZE] && [x] >= [0] && [y] < [g_SIZE]
		//					&& [y] >= [0].
		// Returns:			[short]. Value held at ([x],[y]) in the Grid.
		// Side Effects:	None.
		// Errors:			[errlog] error message if precondition violated.
		//					[g_state] = [false]. Returns [0] if error
		//					occurs. Returns [0] if ![g_state].

		const bool get_state();

		// Purpose:			Returns the current state of the class.
		// Preconditions:	None.
		// Returns:			[bool] [g_state]. If [false], an error has
		//					occured.
		// Side Effects:	None.
		// Errors:			None.

		void set_state(const bool s);

		// Purpose:			Set the state of this class [g_state] to [s].
		//					Use extreme caution with this function as you
		//					have the ability to force the error state to
		//					a possible illogical value.
		// Preconditions:	None.
		// Returns:			None.
		// Side Effects:	None.
		// Errors:			None.

		const short get_dim();

		// Purpose:			Returns dimension of [g_list], [g_SIZE].
		// Preconditions:	None.
		// Returns:			[short] [g_SIZE].
		// Side Effects:	None.
		// Errors:			None.

		void wipe(const short v);

		// Purpose:			Sets every element of the Grid to value [v].
		// Preconditions:	If ![g_state], function exits without wiping.
		//					[v] <= [MAX_VALUE] && [v] >= [MIN_VALUE].
		// Returns:			None.
		// Side Effects:	None.
		// Errors:			[errlog] error message if precondition violated.
		//					[g_state] = [false].

		void replace_all_instances(const short v, const short r);

		// Purpose:			Replace every element of [g_list] that has
		//					the value [v], with the value [r].
		// Preconditions:	If ![g_state], function exits without replacing.
		//					[v] <= [MAX_VALUE] && [v] >= [MIN_VALUE].
		//					[r] <= [MAX_VALUE] && [r] >= [MIN_VALUE].
		// Returns:			None.
		// Side Effects:	None.
		// Errors:			[errlog] error message if precondition violated.
		//					[g_state] = [false].

		void replace_all_non_zero_instances(const short r);

		// Purpose:			Replace every element of [g_list] that satisfies
		//					the unary predicate [is_greater_zero()] with the
		//					the value [r].
		// Preconditions:	If ![g_state], function exits without replacing.
		//					[r] <= [MAX_VALUE] && [r] >= [MIN_VALUE].
		// Returns:			None.
		// Side Effects:	None.
		// Errors:			[errlog] error message if precondition violated.
		//					[g_state] = [false].

		void expire_moving();

		// Purpose:			Replace every element of [g_list] that satisfies
		//					the unary predicate [is_moving_object()] with
		//					[SPACE].
		// Preconditions:	None.
		// Returns:			None.
		// Side Effects:	None.
		// Errors:			None.

		const short count_all_instances(const short v);

		// Purpose:			Counts how many elements in [g_list] that have
		//					the value [v].
		// Preconditions:	If ![g_state], function exits without counting
		//					and returns [0].
		//					[v] <= [MAX_VALUE] && [v] >= [MIN_VALUE].
		// Returns:			[short]. The amount of elements.
		// Side Effects:	None.
		// Errors:			[errlog] error message if precondition violated.
		//					[g_state] = [false].

		const bool find_instance(const short v);

		// Purpose:			If [v] is in [g_list], returns [true], else
		//					returns [false].
		// Preconditions:	If ![g_state], function exits without finding
		//					and returns [false].
		//					[v] <= [MAX_VALUE] && [v] >= [MIN_VALUE].
		// Returns:			[bool]. Whether element found.
		// Side Effects:	None.
		// Errors:			[errlog] error message if precondition violated.
		//					[g_state] = [false].
	
		const void output(ofstream &out);

		// Purpose:			Sends contents of Grid to the supplied
		//					file output stream [out]. Data is written out
		//					in [g_SIZE] rows.
		// Preconditions:	Valid, active stream. If ![g_state], function
		//					exits without data output.
		// Returns:			None.
		// Side Effects:	The stream receives data.
		// Errors:			If [out] failure, function exits with [errlog]
		//					message. [g_state] = [false].

		void input(ifstream &in);

		// Purpose:			Sets the [g_list] to the contents of the file.
		// Preconditions:	If ![g_state], function exits without input.
		//					The file must be ANSI text.
		//					Values in the file must be arranged in [g_SIZE]
		//					columns and [g_SIZE] rows. Each value must be
		//					seperated by a space character [" "]. The
		//					stream must be freshly opened and located at
		//					the first data item (excluding whitespace /
		//					returns).
		// Returns:			None.
		// Side Effects:	None.
		// Errors:			If ![g_state], function exits without processing
		//					the file. If stream failure or end of file
		//					detected before completion, a [errlog] message
		//					is generated. [g_state] = false.
	
		const bool check(const short x, const short y);

		// Purpose:			Analyses whether [x] and [y] are valid
		//					cartesian coordinates for [g_list].
		// Preconditions:	None.
		// Returns:			[bool], [true]/[false].
		// Side Effects:	None.
		// Errors:			None.

		void metamorphose(const short s);
		
		// Purpose:			Destroy the Grid and re-create it using the
		//					dimension [s].
		// Preconditions:	[s] >= MIN_DIMENSION && [s] <= MAX_DIMENSION.
		// Returns:			None.
		// Side Effects:	Every new location value is set to [0].
		//					If succesful, [g_state] = [true].
		// Errors:			[errlog] error message if precondition violation.
		
	private:

		//	*** PRIVATE MEMBER VARIABLES ***
		
		SHORTVECTOR g_list;		// the vector list of coordinate values
		SHORTVECTOR g_lookup;	// lookup table for y reference
		short g_SIZE;			// the dimension of the square Grid
		bool g_state;			// an error state variable, [false] == error

		//	*** PRIVATE FUNCTION PROTOTYPES ***

		void create_lookup();

		// Purpose:			Generates a lookup table for the position of a
		//					y-referenced coordinate. This is used by the
		//					getters and putters to more rapidly compute
		//					locations in the vector on the basis of the
		//					mapping: element E = x + (y * g_SIZE). This
		//					function computes the multiplication in advance
		//					and stores the result in a lookup table referenced
		//					by the y parameter. Therefore, all future vector
		//					location computation only involves addition.
		// Preconditions:	This must be called before any refernces are made
		//					to grid coordinate locations.
		// Returns:			None.
		// Side Effects:	None.
		// Errors:			None.
					
};

//	*** UNARY PREDICATES ***

//	The following simple predicate is used in the function
//	[replace_all_non_zero_instances(const short r)]

class is_greater_zero

{

public:

	const bool operator()(const short &v)

	{

		return(v > 0);

	}

};

//	The following simple predicate is used in the function
//	[expire_moving()]

class is_moving_object

{

public:

	const bool operator()(const short &v)

	{

		return(v >= MINER && v < MINERAL);

	}

};

#endif