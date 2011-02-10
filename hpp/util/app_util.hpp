#ifndef APP_UTIL_HPP
#define APP_UTIL_HPP

#include "tic_tac_toe_types.hpp"
#include <string>

extern direction_t* DIRECTIONS;

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
void cpy_move(move_t* src, move_t* dst);

void set_dir_vals(direction_t* dir, int brd_dir, int row_dir, int col_dir);
void init_directions();
void destroy_directions();
/**
 * defines the conditions needed to be true in order for the current
 * direction is worth checking
 *
 * e.g 4x4 board
 *      _______________
 *     |___|___|___|___|
 *     |___|___|___|_x_| <- won't count pieces diagonally
 *     |___|_x_|___|___| <- count piece diagonally also
 *     |___|___|___|_x_| <- almost all directions are counted
 *
 * /param move - the move played
 * /param dir - the direction
 */
bool dir_conditions(move_t* move, unsigned num_of_boards, unsigned dim, direction_e dir);

std::string player_string(player_e player);

err_composition compose_errors(err_composition e1, err_composition e2);

#endif //APP_UTIL_HPP
