#include "../../hpp/data_structures/ByteArray.hpp"
#include <malloc.h>

#include <iostream>

ByteArray::ByteArray(unsigned num) : _num_of_bytes(num)
{
	_byte = allocate_BYTE(num);
	init_byte_array();
}

ByteArray::ByteArray(const ByteArray& b)
{
	_byte = allocate_BYTE(b.get_num_of_bytes());
	BYTE_memcpy(_byte,b.get_byte(),b.get_num_of_bytes());
}

ByteArray::~ByteArray()
{
	free(_byte);
	_byte = NULL;
}

BYTE* ByteArray::get_byte(unsigned idx) const
{
	BYTE* to_return = NULL;

	if (idx == 0)
		to_return = _byte;
	else if (idx > _num_of_bytes)
		to_return = NULL;
	else
		to_return = &_byte[idx];

	return to_return;
}

ByteArray* ByteArray::get_byte_array(unsigned nob, unsigned idx) const
{
	ByteArray* to_return = NULL;

	if (idx < _num_of_bytes)
	{
		to_return = new ByteArray(nob);
		
		BYTE_memcpy(to_return->get_byte(),this->get_byte(idx),nob);
	}	

	return to_return;
}

bool ByteArray::is_bit_off(unsigned byte_num, unsigned offset)
{
	return and_op((LSB_ONE << (BYTE_SIZE - 1 - offset)),_byte[byte_num]) == 0;
}

unsigned ByteArray::get_num_of_bytes() const
{
	return _num_of_bytes;
}

std::string ByteArray::to_string()
{
	std::string to_return = "";

	unsigned i;
	int j;

	for (i = 0; i < _num_of_bytes; ++i)
	{
		BYTE t_byte = _byte[i];
		for (j = BYTE_SIZE - 1; j >= 0; --j)
		{
			if ((1 << j) & t_byte)
				to_return += STRING_ONE;
			else
				to_return += STRING_ZERO;
		}
	}

	return to_return;
}

void ByteArray::set_bit(unsigned byte_num, unsigned offset)
{
	BYTE t_apply_or_op = or_op((LSB_ONE << (BYTE_SIZE - 1 - offset)),_byte[byte_num]);
	_byte[byte_num] = t_apply_or_op;
}

void ByteArray::reset_bit(unsigned byte_num, unsigned offset)
{
	BYTE t_apply_and_op = and_op((LSB_ZERO << (BYTE_SIZE - 1 - offset)),_byte[byte_num]);
	_byte[byte_num] = t_apply_and_op;
}

/*private*/
void ByteArray::init_byte_array()
{
	unsigned i;
	for (i = 0; i < _num_of_bytes; ++i)
	{
		_byte[i] = 0;
	}
}
