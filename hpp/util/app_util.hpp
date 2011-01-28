#ifndef APP_UTIL_HPP
#define APP_UTIL_HPP

#include "tic_tac_toe_types.hpp"

/*prints the BYTE in a binary fashion*/
void print_binary_BYTE(BYTE* byte);

/*allocates a block of num of BYTEs*/
BYTE* allocate_BYTE(unsigned num);
//static byte_array* allocate_byte_array(unsigned num);

/* copies the memory from src to dest.
 * if src is NULL, NULL is also returned.
 * .....
 */
BYTE* BYTE_memcpy(BYTE* dest, BYTE* src, unsigned num_of_bytes);

move_t* allocate_move();

err_composition compose_errors(err_composition e1, err_composition e2);

#endif //APP_UTIL_HPP
