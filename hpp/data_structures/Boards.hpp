#ifndef BOARDS_HPP
#define BOARDS_HPP

#include "ByteArray.hpp"

class Boards
{
	private:
		unsigned _num_of_boards;
		unsigned _board_dim;
		ByteArray* _x_boards;
		ByteArray* _o_boards;
		ByteArray* _taken;
		int _cell_taken;

		unsigned _space_per_cell; //defaults to 3. number of chars in a cell

		ByteArray* get_board(ByteArray* ba, int idx) const;
		
		/* locate the byte in which the board appears for the first time
		 * NOTE: board idx here starts with 0 and not 1 as in set_move
		 */
		unsigned locate_board_start_idx(unsigned board) const;

		unsigned locate_offset(unsigned board,unsigned row,unsigned col) const;

		/**
		 * /param nob - number of boards
		 */
		unsigned number_of_boards_to_bytes(unsigned nob) const;

		unsigned one_board_size() const;

		/**
		 * this functions is used as a refactoring for the two above functions
		 * returns init_val if is_size_divisible(nob)
		 * or init_val + 1 otherwise
		 *
		 * /param init_val - the initial value to return
		 * /param nob - number of boards
		 */
		unsigned get_bytes(unsigned init_val, unsigned nob) const;

		/**
		 * /param nob - number of boards
		 */
		bool is_size_divisible(unsigned nob) const;

		/**
		 * will check legality of the parameters given and make a move
		 * in case of good params:
		 * - row, col, board are within range
		 * - place requested is not taken
		 *
		 * /param player - player number where 1 is X and 0 is O
		 * /param board - board number
		 * /param row - row number
		 * /param col - col number
		 * /param take_back - undo last move
		 */
		move_err_t set_move(unsigned player,
				unsigned board,
				unsigned row,
				unsigned col,
				bool take_back);

		/*******to_string helper functions*******/

		void cat_board_numbers(std::string& str);

		/**
		 * concatenate the horizontal delimiters
		 *
		 * /param str - string to cat to
		 * /param space_per_char - number of char for each cell
		 */
		void cat_horiz_delimiters(std::string& str);

		/**
		 * concatenate row
		 *
		 * /param str - string to cat to
		 * /param x_str - x boards string
		 * /param o_str - o boards string
		 * /param row - row to cat
		 */
		void cat_row(std::string& str,
				std::string& x_str,
				std::string& o_str,
				unsigned row);

		/*******end to_string helper functions*******/

	public:
		Boards(unsigned num_of_boards, unsigned boards_dim);
		Boards(const Boards& brd);
		~Boards();

		unsigned get_num_of_boards() const;
		unsigned get_board_dim() const;

		/* returns a copy of the board
		 * if board with number num is unavailable NULL is returned
		 * if num < 0 returns a copy of all board array
		 * if num = 0 returns NULL
		 * if 0 < num <= _num_of_boards returns the num-ith board
		 * if num > _num_of_boards returns NULL
		 *
		 * /param idx - index of board to return
		 */
		ByteArray* get_x_board(int idx = -1) const;
		ByteArray* get_o_board(int idx = -1) const;
		ByteArray* get_taken_board(int idx = -1) const;

		int get_cell_taken() const;

		move_err_t player_move(unsigned player,
				unsigned board,
				unsigned row,
				unsigned col,
				bool take_back);

		int get_value_of(move_t* ply);

		std::string to_string(unsigned space = 0);
};

#endif //BOARDS_HPP
