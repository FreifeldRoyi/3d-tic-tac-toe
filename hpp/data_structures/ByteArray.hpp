#ifndef BYTEARRAY_HPP
#define BYTEARRAY_HPP

#include "../util/app_util.hpp"

#include <string>

class ByteArray
{
	private:
		BYTE* _byte;
		unsigned _num_of_bytes;

		void init_byte_array();

	public:
		ByteArray(unsigned num);
		ByteArray(const ByteArray& b);
		~ByteArray();

		unsigned get_num_of_bytes() const;
		/* returns a pointer to the byte in idx location
		 * if idx == 0 returns all byte
		 * by default returns all array
		 * if idx > num_of_bytes returns NULL
		 */
		BYTE* get_byte(unsigned idx = 0) const;

		/* returns a pointer to a new ByteArray
		 * where idx is the location
		 * and nob is the number of bytes to copy
		 * if idx > number of bytes returns NULL
		 * if idx and nob define a longer ByteArray to return than number of bytes available
		 *		returns available bytes only
		 */
		ByteArray* get_byte_array(unsigned nob,unsigned idx) const;
		
		bool is_bit_off(unsigned byte_num, unsigned offset);

		std::string to_string();

		void set_bit(unsigned byte_num, unsigned offset);
		void reset_bit(unsigned byte_num, unsigned offset);
};

#endif //BYTEARRAY_HPP
