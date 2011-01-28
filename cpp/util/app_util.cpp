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

ply_t* allocate_ply()
{
	return (ply_t*)malloc(sizeof(ply_t));
}

err_composition compose_errors(err_composition e1, err_composition e2)
{
	return or_op(e1,e2);
}
