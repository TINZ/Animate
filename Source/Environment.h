//	Filename:		Environment.h
//	Version:		Final
//	Author:			Paul Tinsley (pmbtin)
//	Date:			28 February
//	Platform:		Visual C++ 5.00

//	Symbology:		Numbers, functions and data variables are enclosed in
//					square parentheses "[]". This is to remove any
//					ambiguity within the text of comments. All private data
//					member variables are prefixed by "e_". Any function with
//					the suffix "_f" is a faster version of that function as
//					there is no range/error checking.

//	Errors:			All error messages are appended to the file "errlog.txt"

//	Purpose:		This class utilises the functionality of the class [Grid]
//					to provide a two-dimensional pseudo-environment for the
//					artificial agents to inhabit. This is achieved by having
//					two grids - one for object types and another to hold the
//					quantities related to those objects.		

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

#ifndef __ENVIRONMENT_H
#define __ENVIRONMENT_H

#include "Grid.h"

//	*** CLASS DEFINITION ***

class Environment

{

	public:

		//	*** CONSTRUCTORS ***

		Environment() : e_object(40), e_value(40){};

		// Purpose:			Default constructor.
		// Preconditions:	None.
		// Returns:			An Environment instance.
		// Side Effects:	The Environment is not correctly constructed, unless
		//					a dimension of [40] is required. The member function
		//					[metamorphose(const short s)] may be used to define
		//					the dimensions of [e_object] and [e_value].

		Environment(const short s): e_object(s), e_value(s) {};
		
		// Purpose:			Creates an Enviornment instance based on dimension [s]
		//					and	initialises all contained values to [SPACE].
		// Preconditions:	[s] >= [MIN_DIMENSION] && [s] <= [MAX_DIMENSION].
		// Returns:			An Environment instance.
		// Side Effects:	None.
		// Errors:			[errlog] message from [Grid] if precondition violation.
		//					Program then terminates.

		//	*** OPERATORS ***

		Environment & operator =(const Environment &e);

		// Purpose:			Destructively assigns [e] to the current
		//					context.
		// Preconditions:	None.
		// Returns:			None.
		// Side Effects:	None.
		// Errors:			None.

		//	*** PUBLIC FUNCTION PROTOTYPES ***
		
		void input_objects(ifstream &in);

		// Purpose:			Loads [e_object] and [e_value] with the data contained
		//					in the file located by the stream [in].
		// Preconditions:	[e_object.get_state()] == [true].
		//					The file must be ANSI text.
		//					Values in the file must be arranged in
		//					[e_object.g_SIZE] columns and [e_object.g_SIZE]
		//					rows, first, a set of data must exist for [e_object]
		//					then a newline and a data set for [e_value]. Each
		//					value must be seperated by a space character [" "].
		//					The stream must be freshly opened and located at
		//					the first data item	(excluding whitespace /	returns).
		// Returns:			None.
		// Side Effects:	None.
		// Errors:			If ![e_object.g_state], function exits without
		//					processing the file. If stream failure or end of file
		//					detected before completion, an [errlog] message
		//					is generated. [e_object.g_state] = false.

		const void output_objects(ofstream &out);

		// Purpose:			Sends contents of [e_object] and [e_value] to the
		//					file located by the stream [out].
		// Preconditions:	[e_object.get_state()] == [true].
		//					See [Grid::output(ofstream &out)].
		// Returns:			None.
		// Side Effects:	The file stream.
		// Errors:			If ![e_object.g_state], function exits without
		//					processing the file. An [errlog] message is
		//					generated.

		void put_object(const short x, const short y, const short i, const short q);
		void put_object_f(const short x, const short y, const short i, const short q);

		// Purpose:			Place [i] at the location ([x],[y]) in [e_object] and
		//					record its quantity [q] at the same location in
		//					[e_value].
		// Preconditions:	If (![e_object.g_state] || ![e_value.g_state]), function
		//					exits without putting values.
		//					[x] < [e_object.g_SIZE] && [x] >= [0] && [y] <
		//					[e_object.g_SIZE] && [y] >= [0]. [i] >= [MIN_VALUE] &&
		//					[i] <= [MAX_VALUE]. [q] >= [0] && [q] <= [MAX_VALUE].
		// Returns:			None.
		// Side Effects:	None.
		// Errors:			[errlog] error message if precondition violation.
		//					No action is performed. [e_object.g_state] or
		//					[e_value.g_state] may be set to [false].

		const short get_object(const short x, const short y);
		const short get_object_f(const short x, const short y);

		// Purpose:			Returns value held at the location ([x],[y]) in
		//					[e_object].
		// Preconditions:	If ![e_object.g_state], function exits without
		//					getting and returns [0].
		//					[x] < [e_object.g_SIZE] && [x] >= [0] && [y] <
		//					[e_object.g_SIZE] && [y] >= [0].
		// Returns:			[short]. Value held at ([x],[y]) in [e_object].
		// Side Effects:	None.
		// Errors:			[errlog] error message if precondition violated.
		//					[e_object.g_state] = [false]. Returns [0] if error
		//					occurs. Returns [0] if ![e_object.g_state].
				
		const void get_object(const short x, const short y, short &i, short &q);
		const void get_object_f(const short x, const short y, short &i, short &q);

		// Purpose:			Loads [i] with value held at the location ([x],[y])
		//					in [e_object] and [q] with the quantity held at the
		//					same location in [e_value].
		// Preconditions:	If (![e_object.g_state] || ![e_value.g_state]),
		//					function exits without getting all values.
		//					[x] < [e_object.g_SIZE] && [x] >= [0] && [y] <
		//					[e_object.g_SIZE] && [y] >= [0].
		// Returns:			None.
		// Side Effects:	None.
		// Errors:			[errlog] error message if precondition violated.
		//					[e_object.g_state] or [e_value.g_state] may be set
		//					to [false].
	
		void put_quantity(const short x, const short y, const short q);
		void put_quantity_f(const short x, const short y, const short q);

		// Purpose:			Place [q] at the location ([x],[y]) in [e_value].
		// Preconditions:	If ![e_value.g_state], function exits without
		//					putting value.
		//					[x] < [e_value.g_SIZE] && [x] >= [0] && [y] <
		//					[e_value.g_SIZE] && [y] >= [0]. [q] >= [0] &&
		//					[q] <= [MAX_VALUE].
		// Returns:			None.
		// Side Effects:	None.
		// Errors:			[errlog] error message if precondition violation.
		//					No action is performed. [e_value.g_state] = [false].

		const short get_quantity(const short x, const short y);
		const short get_quantity_f(const short x, const short y);
				
		// Purpose:			Returns value held at the location ([x],[y]) in
		//					[e_value].
		// Preconditions:	If ![e_value.g_state], function exits without
		//					getting and returns [0].
		//					[x] < [e_value.g_SIZE] && [x] >= [0] && [y] <
		//					[e_value.g_SIZE] && [y] >= [0].
		// Returns:			[short]. Value held at ([x],[y]) in [e_value].
		// Side Effects:	None.
		// Errors:			[errlog] error message if precondition violated.
		//					[e_value.g_state] = [false]. Returns [0] if error
		//					occurs. Returns [0] if ![e_value.g_state].

		short take_quantity(const short x, const short y, const short a);
		short take_quantity_f(const short x, const short y, const short a);

		// Purpose:			If sufficient quantity in [e_value] exists that
		//					exceeds [a], returns [a] and deducts [a] from
		//					the quantity held at [e_value]. Otherwise returns
		//					a value that is less than [a], returns that value
		//					and sets the value at ([x],[y]) in [e_object] to
		//					[SPACE] in order to record the fact that the object
		//					no longer exists.
		// Preconditions:	If ![e_value.g_state], function exits without
		//					getting and returns [0].
		//					[e_object.get([x],[y])] != [SPACE].
		//					[x] < [e_value.g_SIZE] && [x] >= [0] && [y] <
		//					[e_value.g_SIZE] && [y] >= [0].
		// Returns:			[short]. Portion or all of value held at ([x],[y])
		//					in [e_value].
		// Side Effects:	See Purpose.
		// Errors:			[errlog] error message if precondition violated.
		//					[e_value.g_state] = [false]. Returns [0] if error
		//					occurs. Returns [0] if ![e_value.g_state].

		bool add_quantity(const short x, const short y, const short i, const short a);
		bool add_quantity_f(const short x, const short y, const short i, const short a);

		// Purpose:			If sufficient quantity in [e_value] exists that
		//					allows [a] to be added to it, returns [true] and
		//					adds [a] to the quantity held at [e_value].
		//					Otherwise returns [false].
		// Preconditions:	If ![e_value.g_state], function exits without
		//					putting and returns [false].
		//					[e_object.get([x],[y])] == [i] || [e_object.get([x],[y])
		//					== SPACE) || [e_object.get([x],[y]) == [HOME] ||
		//					[e_object.get([x],[y]) == [ORE] || [e_object.get([x],[y])
		//					== [CARCASS].
		//					[x] < [e_value.g_SIZE] && [x] >= [0] && [y] <
		//					[e_value.g_SIZE] && [y] >= [0].
		// Returns:			[bool].
		// Side Effects:	None.
		// Errors:			[errlog] error message if [x] or [y] precondition violated.
		//					[e_value.g_state] and [e_object.g_state] may be set to
		//					[false]. Returns [false] if error occurs.

		void rand_all_quantities(const short o, const short min, const short max);

		// Purpose:			For all objects [o] found in [e_object], sets their
		//					quantities in [e_value] to a random value between
		//					[min] and [max].
		// Preconditions:	If (![e_object.g_state] || ![e_value.g_state]), function
		//					exits without putting values.
		//					[o] >= [MIN_VALUE] && [o] <= [MAX_VALUE].
		//					[min] >= [MIN_VALUE] && [min] <= [MAX_VALUE].
		//					[max] >= [MIN_VALUE] && [max] <= [MAX_VALUE].
		//					[max] > [min].
		// Returns:			None.
		// Side Effects:	None.
		// Errors:			[errlog] error message if precondition violated.

		void set_all_quantities(const short o, const short v);

		// Purpose:			For all objects [o] found in [e_object], sets their
		//					quantities in [e_value] to a the value [v].
		// Preconditions:	If (![e_object.g_state] || ![e_value.g_state]), function
		//					exits without putting values.
		//					[o] >= [MIN_VALUE] && [o] <= [MAX_VALUE].
		//					[v] >= [MIN_VALUE] && [v] <= [MAX_VALUE].
		// Returns:			None.
		// Side Effects:	None.
		// Errors:			[errlog] error message if precondition violated.

		void metamorphose(const short s);

		// Purpose:			Destroy [e_object] and [e_value].
		//					Then re-create them using the dimension [s].
		// Preconditions:	[s] >= MIN_DIMENSION && [s] <= MAX_DIMENSION.
		// Returns:			None.
		// Side Effects:	Every new location value is set to [0].
		//					If succesful, [e_object.g_state] = [true] and
		//					[e_value.g_state] = [true].
		// Errors:			[errlog] error message if precondition violation.
		//					[e_object.g_state] = [false] and [e_value.g_state]
		//					= [false].

		void clear_objects(const short o);

		// Purpose:			Sets all values in [e_object] that are type [o]
		//					to [0] and sets their corresponding values in
		//					[e_value] to [0].
		// Preconditions:	If ![e_object.g_state], function exits without
		//					clearing.
		// Returns:			None.
		// Side Effects:	None.
		// Errors:			None.
		
		void clear_all();

		// Purpose:			Sets all values in [e_object] and [e_value]
		//					to [0].
		// Preconditions:	If ![e_object.g_state], objects will not clear.
		//					If ![e_value.g_state], values will not clear.
		// Returns:			None.
		// Side Effects:	None.
		// Errors:			None.

		const short get_dim();

		// Purpose:			Returns the dimension of the environment.
		// Preconditions:	None.
		// Returns:			[short].
		// Side Effects:	None.
		// Errors:			None.

		const bool check_coord(const short x, const short y);

		// Purpose:			Analyses whether [x] and [y] are valid
		//					cartesian coordinates for the environment.
		// Preconditions:	None.
		// Returns:			[bool], [true]/[false].
		// Side Effects:	None.
		// Errors:			[errlog] error message if invalid coordinates.

		void get_all_objects(Grid &g);

		// Purpose:			Copies entire contents of [e_object] to [g].
		// Preconditions:	None.
		// Returns:			None.
		// Side Effects:	Caution re grids not same dimension.
		// Errors:			None.

		const bool get_state();

		// Purpose:			If [e_object.get_state()] == [false] ||
		//					[e_value.get_state()] == [false], returns
		//					[false], else returns [true].
		// Preconditions:	None.
		// Returns:			None.
		// Side Effects:	None.
		// Errors:			None.

		const bool contains_object(const short v);

		// Purpose:			If [e_object] contains [v], returns [true], else
		//					returns [false].
		// Preconditions:	None.
		// Returns:			None.
		// Side Effects:	None.
		// Errors:			None.
	
	private:

		//	*** PRIVATE MEMBER VARIABLES ***
		
		Grid e_object;			// objects in the environment
		Grid e_value;			// quantity of objects in the environment
		
};

#endif