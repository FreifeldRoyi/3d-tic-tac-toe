/*
 * Minimax.cpp
 *
 *  Created on: Feb 8, 2011
 *      Author: freifeldroyi
 */

#include "../../hpp/AI_planning/Minimax.hpp"
#include <math.h>

Minimax::Minimax(int num_of_ply) : _num_of_ply(num_of_ply)
{
	_directions = init_directions();
}

Minimax::~Minimax()
{
	destroy_directions(_directions);
}

void Minimax::set_num_of_ply(int nop)
{
	_num_of_ply = nop;
}

move_t* Minimax::best_move(Boards* cur_brd, player_e pl)
{
	//TODO
}

/*private*/

Minimax::_tree_node_t* Minimax::create_tree_node(Boards* brd)
{

}


void Minimax::count_direction(Boards* board,
		move_t cur_idx,
		direction_t* dir,
		int* player_count,
		int* opp_count)
{
	if (dir->brd_dir != 0 || dir->row_dir != 0 || dir->col_dir != 0)
	{
		if (IN_RANGE(cur_idx.row,board->get_board_dim()) &&
				IN_RANGE(cur_idx.col,board->get_board_dim()) &&
				IN_RANGE(cur_idx.board,board->get_board_dim()))
		{
			player_e player = board->whos_bit_on(&cur_idx);
			if (player == cur_idx.player)
			{
				++(*player_count);
			}
			else if (CHANGE_PLAYER(cur_idx.player) == player)
			{
				++(*opp_count);
			}
			else {} //bit is off

			cur_idx.row += dir->row_dir;
			cur_idx.col += dir->col_dir;
			cur_idx.board += dir->brd_dir;
			count_direction(board,cur_idx,dir,player_count,opp_count);
		}
	}
}

void Minimax::apply_direction_count(Boards* board,
		move_t* cur_idx,
		direction_e dir,
		int* player_count,
		int* opp_count)
{
	if (dir_conditions(board,cur_idx,dir))
	{
		direction_t t_dir = _directions[dir];
		count_direction(board,*cur_idx,&t_dir,player_count,opp_count);

		t_dir.brd_dir = -t_dir.brd_dir;
		t_dir.row_dir = -t_dir.row_dir;
		t_dir.col_dir = -t_dir.col_dir;
		count_direction(board,*cur_idx,&t_dir,player_count,opp_count);
	}
}

bool Minimax::dir_conditions(Boards* board, move_t* move, direction_e dir) const
{
	bool to_return;

	switch (dir)
	{
		case (DIR_SNGL_ROW):
			to_return = true;
			break;

		case (DIR_SNGL_COL):
			to_return = true;
			break;

		case (DIR_SNGL_DIAG_UL_DR):
			to_return = move->row == move->col;
			break;

		case (DIR_SNGL_DIAG_UR_DL):
			to_return = move->row + move->col == board->get_board_dim() - 1;
			break;

		case (DIR_MULT_ROW_TL_BR):
			to_return = move->col == move->board;
			break;

		case (DIR_MULT_ROW_TR_BL):
			to_return = move->board == board->get_board_dim() - 1 - move->col;
			break;

		case (DIR_MULT_COL_TU_BD):
			to_return = move->row == move->board;
			break;

		case (DIR_MULT_COL_TD_BU):
			to_return = move->board == board->get_board_dim() - 1 - move->row;
			break;

		case (DIR_MULT_DIAG_TUR_BDL):
			to_return = move->row + move->col == board->get_board_dim() - 1 && move->row == move->board;
			break;

		case (DIR_MULT_DIAG_TUL_BDR):
			to_return = move->row == move->col && move->board == move->row;
			break;

		case (DIR_MULT_DIAG_TDL_BUR):
			to_return = move->row + move->col == board->get_board_dim() - 1 && move->board == move->col;
			break;

		case (DIR_MULT_DIAG_TDR_BUL):
			to_return = move->row == move->col && move->board == board->get_board_dim() - 1 - move->row;
			break;

		case (DIR_MULT_PIERCE):
			to_return = true;
			break;

		default:
			to_return = false;
	}

	return to_return;
}

double Minimax::calc_hueristic(Boards* board, move_t* move)
{
	double to_return = 0;
	int second_power = 1;
	int player_lines[board->get_board_dim()];
	int opp_lines[board->get_board_dim()];

	int player_count;
	int opp_count;

	for (int i = 0; i < static_cast<int>(board->get_board_dim()); ++i)
	{
		player_lines[i] = 0;
		opp_lines[i] = 0;
	}

	for (int dir = DIR_SNGL_ROW; dir < NUMBER_OF_DIRECTIONS; ++dir)
	{
		player_count = 0;
		opp_count = 0;

		apply_direction_count(board,move,(direction_e)dir,&player_count,&opp_count);
		++player_lines[player_count];
		++opp_lines[opp_count];
	}

	to_return += player_lines[0] - opp_lines[0];
	for (int i = 1; i < static_cast<int>(board->get_board_dim()); ++i)
	{
		to_return += pow10(second_power) * (player_lines[i] - opp_lines[i]);
		second_power *= 2;
	}

	return to_return;
}
