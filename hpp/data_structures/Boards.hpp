#ifndef BOARDS_HPP
#define BOARDS_HPP

#include "ByteArray.hpp"

#define ON_LEFT_RIGHT_DIAG(board,dim,row,col) ((row) == (col))
#define ON_RIGHT_LEFT_DIAG(board,dim,row,col) ((row) + (col) == ((dim) - 1))
#define BOARD_SPREAD(board,dim,row,col) ((row) == (board))

class Boards
{
	private:
		unsigned _num_of_boards;
		unsigned _board_dim;

		double _static_heuristic; //static heuritic function
		int _empty_slots; //empty slots left on the board

		ByteArray* _x_boards;
		ByteArray* _o_boards;
		ByteArray* _taken;

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
		move_err_t set_move(move_t* move,
				bool take_back);

		/**
		 * TODO
		 */
		int single_board_row_count(move_t* move);

		/**
		 * TODO
		 */
		int single_board_col_count(move_t* move);

		/**
		 * TODO
		 */
		int single_board_diag_count(move_t* move);

		/**
		 * TODO
		 */
		int multi_board_row_count(move_t* move);

		/**
		 * TODO
		 */
		int multi_board_col_count(move_t* move);

		/**
		 * TODO
		 */
		int multi_board_diag_count(move_t* move);

		/**
		 * TODO
		 */
		int multi_board_pierce_col_count(move_t* move);

		/** TODO
		 * calculates the new static heuristic value after
		 * the move given as a parameter
		 *
		 * /param player - the player idx
		 * /param board - the board idx
		 * /param row - the row idx
		 * /param col - the column idx
		 */
		double calc_hueristic(move_t* move);

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

		double get_heuristic_value() const;

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

		move_err_t player_move(move_t* move,
				bool take_back);

		std::string to_string(unsigned space = 0);
};

#endif //BOARDS_HPP
