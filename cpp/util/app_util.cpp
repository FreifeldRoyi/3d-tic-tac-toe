#include "../../hpp/util/app_util.hpp"

#include <assert.h>
#include <malloc.h>
#include <iostream>

using namespace std;

void print_binary_BYTE(BYTE* byte)
{
	int i;

	for (i = BYTE_SIZE - 1; i >= 0; --i)
	{
		if ((1 << i) & (*byte))
		{
			cout << STRING_ONE;
		}
		else
		{
			cout << STRING_ZERO;
		}
	}

	cout << endl;
}

BYTE* allocate_BYTE(unsigned num)
{
	BYTE* to_return = NULL;
	
	if (num > 0)
	{
		to_return = (BYTE*)malloc(num);
		assert(to_return != NULL);
	}

	return to_return;
}

BYTE* BYTE_memcpy(BYTE* dest, BYTE* src, unsigned num_of_bytes)
{
	unsigned i;

	if (src != NULL)
	{
		if (dest != NULL)
		{
			for (i = 0; i < num_of_bytes; ++i)
			{
				dest[i] = src[i];
			}
		}
	}
	
	return dest;
}

move_t* allocate_move()
{
	return (move_t*)malloc(sizeof(move_t));
}

void set_dir_vals(direction_t* dir, int brd_dir, int row_dir, int col_dir)
{
	dir->brd_dir = brd_dir;
	dir->row_dir = row_dir;
	dir->col_dir = col_dir;
}

direction_t* init_directions()
{
	direction_t* to_return = (direction_t*)malloc(sizeof(direction_t) * NUMBER_OF_DIRECTIONS);

	set_dir_vals(&to_return[DIR_SNGL_ROW],0,0,1);
	set_dir_vals(&to_return[DIR_SNGL_COL],0,1,0);
	set_dir_vals(&to_return[DIR_SNGL_DIAG_UL_DR],0,1,1);
	set_dir_vals(&to_return[DIR_SNGL_DIAG_UR_DL],0,1,-1);
	set_dir_vals(&to_return[DIR_MULT_ROW_TL_BR],1,0,1);
	set_dir_vals(&to_return[DIR_MULT_ROW_TR_BL],1,0,-1);
	set_dir_vals(&to_return[DIR_MULT_COL_TU_BD],1,1,0);
	set_dir_vals(&to_return[DIR_MULT_COL_TD_BU],1,-1,0);
	set_dir_vals(&to_return[DIR_MULT_DIAG_TUR_BDL],1,1,-1);
	set_dir_vals(&to_return[DIR_MULT_DIAG_TUL_BDR],1,1,1);
	set_dir_vals(&to_return[DIR_MULT_DIAG_TDL_BUR],1,-1,1);
	set_dir_vals(&to_return[DIR_MULT_DIAG_TDR_BUL],1,-1,-1);
	set_dir_vals(&to_return[DIR_MULT_PIERCE],1,0,0);

	return to_return;
}

void destroy_directions(direction_t* dir)
{
	delete dir;
}

err_composition compose_errors(err_composition e1, err_composition e2)
{
	return or_op(e1,e2);
}
