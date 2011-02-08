/*
 * Minimax.cpp
 *
 *  Created on: Feb 8, 2011
 *      Author: freifeldroyi
 */

#include "../../hpp/AI_planning/Minimax.hpp"
#include <math.h>
#include <malloc.h>
#include <limits>

Minimax::Minimax(player_e player, int num_of_ply) : _num_of_ply(num_of_ply), _player(player)
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

void Minimax::best_move(Boards* cur_brd, player_e player, move_t* move)
{
	struct _node_data_t* t_top_node = generate_top_node(cur_brd);
	switch (player)
	{
		case (O_PLAYER): //minimizer
			do_minimax(t_top_node,-INFINITY,+INFINITY,_num_of_ply - 1);
			break;

		case (X_PLAYER): //maximizer
			do_maximin(t_top_node,-INFINITY,+INFINITY,_num_of_ply - 1);
			break;

		default:
			do_minimax(t_top_node,-INFINITY,+INFINITY,_num_of_ply - 1);
			break;
	};

	//cpy_move(&t_top_node->best_move,move);
}

/*private*/

Minimax::_node_data_t* Minimax::generate_top_node(Boards* board)
{
	struct _node_data_t* to_return = create_tree_node();

	to_return->current = new Boards(*board);
	to_return->unex_children = board->possible_moves(_player);

	return to_return;
}

void Minimax::generate_child(struct _node_data_t* father)
{
	struct _node_data_t* to_add = create_tree_node();

	Boards* board = new Boards(*(father->current));

	move_t* t_mv = father->unex_children->front(); //TODO refactor later //access child move
	board->player_move(t_mv,false);

	to_add->current = board;
	to_add->value = calc_hueristic(father->current,t_mv);
	to_add->unex_children = board->possible_moves(CHANGE_PLAYER(t_mv->player)); //child moves will be opponent's moves

	if (father->last_child == NULL) // first child expansion
	{
		father->first_child = to_add;
		father->last_child = to_add;
	}
	else
	{
		father->last_child->brother = to_add;
	}
	++father->num_ex_child;
	father->unex_children->pop_front(); //TODO refactor later
	to_add->father = father;
}

Minimax::_node_data_t* Minimax::create_tree_node()
{
	struct _node_data_t* to_return = (Minimax::_node_data_t*)malloc(sizeof(Minimax::_node_data_t));

	to_return->current = NULL;
	to_return->value = 0;
	to_return->father = NULL;
	to_return->brother = NULL;
	to_return->first_child = NULL;
	to_return->last_child = NULL;
	to_return->num_ex_child = 0;
	to_return->unex_children = NULL;

	return to_return;
}

void Minimax::destroy_tree_node(Minimax::_node_data_t* node)
{
	delete node->current;
	node->current = NULL;

	struct _node_data_t* t_child = node->first_child;

	while (t_child != NULL)
	{
		struct _node_data_t* t_brother = t_child->brother;
		destroy_tree_node(t_child);
		t_child = t_brother;
	}
	node->first_child = NULL;

	while (!node->unex_children->empty())
	{
		node->unex_children->pop_front(); //TODO refactor later
	}
	delete node->unex_children;
	node->unex_children = NULL;
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

double Minimax::do_maximin(Minimax::_node_data_t* node, double alpha, double beta, int depth)
{
	if (depth == 0)
	{
		return node->value;
	}
	std::list<move_t*>::iterator it = node->unex_children->begin();
	while (it != node->unex_children->end())
	{
		generate_child(node);
		double value = do_minimax(node->last_child,alpha,beta,depth - 1);

		if (value > alpha)
		{
			alpha = value;
		}
		if (alpha >= beta)
		{
			return alpha;
		}

		it = node->unex_children->begin();
	}

	return alpha;
}

double Minimax::do_minimax(Minimax::_node_data_t* node, double alpha, double beta, int depth)
{
	if (depth == 0)
	{
		return node->value;
	}
	std::list<move_t*>::iterator it = node->unex_children->begin();
	while (it != node->unex_children->end())
	{
		generate_child(node);
		double value = do_maximin(node->last_child,alpha,beta,depth - 1);

		if (value < beta)
		{
			beta = value;
		}
		if (beta <= alpha)
		{
			return beta;
		}

		it = node->unex_children->begin();
	}

	return beta;
}
