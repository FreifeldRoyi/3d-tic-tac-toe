#include "../../hpp/data_structures/Boards.hpp"
#include <sstream>

#define MAX_SPACE_PER_CELL 20

Boards::Boards(unsigned num_of_boards, unsigned boards_dim) : 
	_num_of_boards(num_of_boards), 
	_board_dim(boards_dim)
{
	//_x_boards = new ByteArray(number_of_boards_to_bytes(num_of_boards));
	//_o_boards = new ByteArray(number_of_boards_to_bytes(num_of_boards));
	_boards[O_PLAYER] = new ByteArray(number_of_boards_to_bytes(num_of_boards));
	_boards[X_PLAYER] = new ByteArray(number_of_boards_to_bytes(num_of_boards));
	_taken = new ByteArray(number_of_boards_to_bytes(num_of_boards));

	_empty_slots = boards_dim * boards_dim * num_of_boards;



	_space_per_cell = 3;
}

Boards::Boards(const Boards& brd)
{
	_num_of_boards = brd.get_num_of_boards();
	_board_dim = brd.get_board_dim();

	_empty_slots = brd.get_cell_taken();

	_boards[O_PLAYER] = brd.get_o_board();
	_boards[X_PLAYER] = brd.get_x_board();
	//_o_boards = brd.get_o_board();
	//_x_boards = brd.get_x_board();
	_taken = brd.get_taken_board();

	_space_per_cell = 3;
}

Boards::~Boards()
{
	//delete _x_boards;
	//delete _o_boards;
	delete _boards[O_PLAYER];
	delete _boards[X_PLAYER];
	delete _taken;
}

unsigned Boards::get_num_of_boards() const
{
	return _num_of_boards;
}

unsigned Boards::get_board_dim() const
{
	return _board_dim;
}

ByteArray* Boards::get_x_board(int idx) const
{
	//return get_board(_x_boards,idx);
	return get_board(_boards[X_PLAYER],idx);
}

ByteArray* Boards::get_o_board(int idx) const
{
	//return get_board(_o_boards,idx);
	return get_board(_boards[O_PLAYER],idx);
}

ByteArray* Boards::get_taken_board(int idx) const
{
	return get_board(_taken,idx);
}

int Boards::get_cell_taken() const
{
	return _empty_slots;
}

move_err_e Boards::player_move(move_t* move,
		bool take_back)
{
	return set_move(move,take_back);
}

std::string Boards::to_string(unsigned space)
{
	std::string to_return = "";
	//std::string t_x_string = _x_boards->to_string();
	//std::string t_o_string = _o_boards->to_string();
	std::string t_x_string = _boards[X_PLAYER]->to_string();
	std::string t_o_string = _boards[O_PLAYER]->to_string();

	unsigned row;

	if (space != 0 && space < MAX_SPACE_PER_CELL)
	{
		if (space % 2 == 0)
			_space_per_cell = space - 1;
		else
			_space_per_cell = space;
	}

	cat_board_numbers(to_return);
	to_return += '\n';
	cat_horiz_delimiters(to_return);
	to_return += '\n';
	for (row = 0; row < _board_dim; ++row)
	{
		cat_row(to_return,t_x_string,t_o_string,row);
		to_return += '\n';
		cat_horiz_delimiters(to_return);
		to_return += '\n';
	}

	return to_return;
}

/*private*/
ByteArray* Boards::get_board(ByteArray* ba, int idx) const
{
	ByteArray* to_return = NULL;

	if (idx < 0)
		to_return = ba->get_byte_array(number_of_boards_to_bytes(_num_of_boards),0);
	else
		to_return = ba->get_byte_array(one_board_size(),idx);
	
	return to_return;
}

unsigned Boards::number_of_boards_to_bytes(unsigned nob) const
{
	return get_bytes(locate_board_start_idx(nob),nob);
}

unsigned Boards::one_board_size() const
{
	return get_bytes(_num_of_boards / BYTE_SIZE,_num_of_boards);
}

unsigned Boards::get_bytes(unsigned init_val, unsigned nob) const
{
	unsigned to_return = init_val;

	if (!is_size_divisible(nob))
		++to_return;

	return to_return;
}

bool Boards::is_size_divisible(unsigned nob) const
{
	return locate_offset(nob,0,0) == 0;
}

void Boards::overflow_handle(move_t* move, unsigned* byte, unsigned* offset)
{
	(*byte) = locate_board_start_idx(move->board); //starting BYTE idx
	(*offset) = locate_offset(move->board,move->row,move->col); //bit to change offset from the beginning of BYTE

	if ((*offset) >= BYTE_SIZE) //overflow handling
	{
		unsigned t_bytes_in_off = (*offset) / BYTE_SIZE; //how many BYTEs to jump ahead
		(*byte) += t_bytes_in_off;
		(*offset) -= t_bytes_in_off * BYTE_SIZE; //removing unneeded bits from calculation
	}
}

unsigned Boards::locate_offset(unsigned board,unsigned row,unsigned col) const
{
	return _board_dim * row + 
		col + 
		(_board_dim * _board_dim * board) % BYTE_SIZE;
}

unsigned Boards::locate_board_start_idx(unsigned board) const
{
	return (_board_dim * _board_dim * board) / BYTE_SIZE;
}

move_err_e Boards::set_move(move_t* move,
		bool take_back)
{
	move_err_e to_return = ERR_OK;
	ByteArray* t_move_board = NULL;
	
	if (move->player >= 0 && move->player < 2) //TODO const it
		t_move_board = _boards[move->player];
	/*	t_move_board = _x_boards;
	else if (move->player == 0)
		t_move_board = _o_boards;*/

	if (t_move_board != NULL)
	{
		if (move->board < _num_of_boards)
		{
			if (move->row < _board_dim)
			{
				if (move->col < _board_dim)
				{
					unsigned t_byte_start_idx;// = locate_board_start_idx(move->board); //starting BYTE idx
					unsigned t_bit_to_change;// = locate_offset(move->board,move->row,move->col); //bit to change offset from the beginning of BYTE

					/*if (t_bit_to_change >= BYTE_SIZE) //overflow handling
					{
						unsigned t_bytes_in_off = t_bit_to_change / BYTE_SIZE; //how many BYTEs to jump ahead
						t_byte_start_idx += t_bytes_in_off;
						t_bit_to_change -= t_bytes_in_off * BYTE_SIZE; //removing unneeded bits from calculation
					}*/
					overflow_handle(move,&t_byte_start_idx,&t_bit_to_change);

					if (_taken->is_bit_off(t_byte_start_idx,t_bit_to_change)) //place not taken
					{
						if (!take_back) //normal move
						{
							t_move_board->set_bit(t_byte_start_idx,t_bit_to_change); //set the correct bit
							_taken->set_bit(t_byte_start_idx,t_bit_to_change); //mark place as taken
							--_empty_slots;
							to_return = ERR_OK;
						}
						else
							to_return = ERR_MOVE_ILLEGAL;
					}
					else if (take_back) //undo last move
					{
						t_move_board->reset_bit(t_byte_start_idx,t_bit_to_change);
						to_return = ERR_OK;
					}
					else
						to_return = ERR_MOVE_ILLEGAL;
				}
				else
					to_return = ERR_COL;
			}
			else
				to_return = ERR_ROW;
		}
		else
			to_return = ERR_BOARD;
	}
	else
		to_return = ERR_START;

	return to_return;
}

int Boards::whos_bit_on(move_t* move)
{
	int to_return = -1;
	unsigned t_loop_byte;
	unsigned t_loop_bit;

	overflow_handle(move,&t_loop_byte,&t_loop_bit);
	if (!_taken->is_bit_off(t_loop_byte,t_loop_bit)) //if bit on
	{
		if (_boards[CHANGE_PLAYER(move->player)]->is_bit_off(t_loop_byte,t_loop_bit)) //other player's bit is off => player's bit is on
		{
			to_return = move->player;
		}
		else //other player's bit is on
		{
			to_return = CHANGE_PLAYER(move->player);
		}
	} //else to_return = 0 but already initialized

	return to_return;
}

/*******to_string helper functions*******/

/**
 * thickens every appending to str with
 * ( space_per_cell - 1 ) / 2
 * padding from each side of to_app
 */
void thicken_append(std::string& str, char to_app, unsigned space_per_cell)
{
	unsigned t_thick_per_side = (space_per_cell - 1) / 2;

	unsigned i;
	for (i = 0; i < t_thick_per_side; ++i)
		str += " ";

	str += to_app;

	for (i = 0; i < t_thick_per_side; ++i)
		str += " ";
}

inline unsigned num_of_delimiters(unsigned chars_for_cell, unsigned dim)
{
	return dim * chars_for_cell + dim + 1;
}

void cat_padding(std::string& str, unsigned padding_size)
{
	unsigned i;
	for (i = 0; i < padding_size; ++i)
		str += ' ';
}

unsigned number_of_digits(unsigned num)
{
	unsigned to_return = 0;
	int t_n = num;

	do
	{
		t_n = t_n / 10;
		++to_return;
	} while(t_n != 0);

	return to_return;
}

void Boards::cat_board_numbers(std::string& str)
{
	unsigned delim_num = num_of_delimiters(_space_per_cell, _board_dim);

	unsigned board_num;
	for (board_num = 0; board_num < _num_of_boards; ++ board_num)
	{
		//integer to string conversion
		std::stringstream t_ss;
		t_ss << board_num;
		//end conversion

		unsigned i, digit_num = number_of_digits(board_num);
		str += t_ss.str() + ':';

		for (i = 0; i < delim_num - digit_num - 1; ++i)
			str += ' ';

		cat_padding(str,delim_num / 2);
	}
}

void Boards::cat_horiz_delimiters(std::string& str)
{
	unsigned i, j;

	char t_horiz_delim = '-';

	unsigned delim_num = num_of_delimiters(_space_per_cell,_board_dim);

	for (j = 0; j < _num_of_boards; ++j)
	{
		for (i = 0; i < delim_num; ++i)
			str += t_horiz_delim;

		if (j != _num_of_boards - 1)
			cat_padding(str,delim_num / 2);
	}
}

void Boards::cat_row(std::string& str,
		std::string& x_str,
		std::string& o_str,
		unsigned row)
{
	unsigned col,board_num;
	unsigned delim_num = num_of_delimiters(_space_per_cell,_board_dim);

	char t_x_char = 'x';
	char t_o_char = 'o';
	char t_place_holder = ' ';
	char t_vert_delim = '|';

	for (board_num = 0; board_num < _num_of_boards; ++board_num)
	{
		str += t_vert_delim;
		for (col = 0; col < _board_dim; ++col)
		{
			if (x_str[board_num * _board_dim * _board_dim + row * _board_dim + col] == '1')
				thicken_append(str,t_x_char,_space_per_cell);
			else if (o_str[board_num * _board_dim * _board_dim + row * _board_dim + col] == '1')
				thicken_append(str,t_o_char,_space_per_cell);
			else
				thicken_append(str,t_place_holder,_space_per_cell);

			str += t_vert_delim;
		}

		cat_padding(str,delim_num / 2);
	}
}

/*******end to_string helper functions*******/


