#ifndef BOARDS_HPP
#define BOARDS_HPP

#include "ByteArray.hpp"

#include <list>

#define IN_RANGE(idx,upper_bound) (((idx) >= 0) && ((idx) < (upper_bound)))

class Boards
{
	private:
		unsigned _num_of_boards;
		unsigned _board_dim;

		int _empty_slots; //empty slots left on the board
		victory_e _game_end;

		ByteArray* _boards[NUM_OF_PLAYERS];
		ByteArray* _taken;

		unsigned _space_per_cell; //defaults to 3. number of chars in a cell used for to_string

		ByteArray* get_board(ByteArray* ba, int idx) const;
		
		/**
		 * calculating board start byte and bit to change offset,
		 * offset is relative to board start byte
		 * returns the actual byte and offset from that byte of the bit
		 *
		 * /param move - the move to be carried
		 * /param byte - output parameter
		 * /param offset - output parameter
		 */
		void overflow_handle(move_t* move, unsigned* byte, unsigned* offset);

		/* locate the byte in which the board appears for the first time
		 */
		unsigned locate_board_start_idx(unsigned board) const;

		/**
		 * returns the offset of the bit representing the slot given (board,row,col)
		 * bit offset is relative to the board start byte
		 */
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
		 * /param move - the move
		 * /param take_back - undo last move
		 */
		move_err_e set_move(move_t* move,
				bool take_back);

		bool count_direction(move_t cur_idx, direction_t* dir);
		bool apply_direction_count(move_t* move, direction_e dir); //TODO refactor later somehow with one in Minimax
		void end_check(move_t* move);

		void dec_empty_slots();
		void inc_empty_slots();

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

		/**
		 * returns the player whos bit is on
		 * or the number of players if no bit is on
		 */
		player_e whos_bit_on(move_t* move);

		/* returns a copy of the board
		 * if board with number idx is unavailable NULL is returned
		 * if idx < 0 returns a copy of all board array
		 * if idx = 0 returns NULL
		 * if 0 < idx <= _num_of_boards returns the idx-ith board
		 * if idx > _num_of_boards returns NULL
		 *
		 * /param idx - index of board to return
		 */
		ByteArray* get_x_board(int idx = -1) const;
		ByteArray* get_o_board(int idx = -1) const;
		ByteArray* get_taken_board(int idx = -1) const;

		int get_empty_slots() const;

		move_err_e player_move(move_t* move,
				bool take_back);

		/**
		 * returns all possible moves on board
		 */
		std::list<move_t>* possible_moves(player_e player);

		victory_e get_game_state() const;
		bool block_check(move_t* move);

		std::string to_string(unsigned space = 0);
};

#endif //BOARDS_HPP
