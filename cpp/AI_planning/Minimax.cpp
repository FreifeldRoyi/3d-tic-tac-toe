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

//TODO delete later
#include <iostream>
//TODO delete later

#define CHANGE_MINIMAX_TYPE(type) (static_cast<minimax_type_e>(1 - (type)))

Minimax::Minimax(player_e player, int num_of_ply) : _num_of_ply(num_of_ply), _player(player)
{
	//_directions = init_directions();
	_best_moves = NULL;
	_best_val = -INFINITY;
}

Minimax::~Minimax()
{
	destroy_directions();
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
			apply_minimax(t_top_node,-INFINITY,+INFINITY,_num_of_ply,MINIMIZE);
			break;

		case (X_PLAYER): //maximizer
			apply_minimax(t_top_node,-INFINITY,+INFINITY,_num_of_ply,MAXIMIZE);
			break;

		default:
			apply_minimax(t_top_node,-INFINITY,+INFINITY,_num_of_ply,MINIMIZE);
			break;
	};

	cpy_move(&t_top_node->best_move,move);
	destroy_tree_node(t_top_node);
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

	move_t t_mv = father->unex_children->front(); //TODO refactor later //access child move
	board->player_move(&t_mv,false);

	//TODO delete
	std::cout << board->to_string() << std::endl;
	//TODO end delete

	to_add->current = board;
	to_add->value = calc_hueristic(father->current,&t_mv);
	to_add->unex_children = board->possible_moves(CHANGE_PLAYER(t_mv.player)); //child moves will be opponent's moves

	cpy_move(&t_mv,&to_add->move_played);
	cpy_move(&t_mv,&to_add->best_move);

	if (father->last_child == NULL) // first child expansion
	{
		father->first_child = to_add;
		father->last_child = to_add;
	}
	else
	{
		father->last_child->brother = to_add;
		father->last_child = to_add;
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
		cur_idx.row += dir->row_dir;
		cur_idx.col += dir->col_dir;
		cur_idx.board += dir->brd_dir;

		if (IN_RANGE(cur_idx.row,board->get_board_dim()) &&
				IN_RANGE(cur_idx.col,board->get_board_dim()) &&
				IN_RANGE(cur_idx.board,board->get_board_dim()))
		{
			player_e player = board->whos_bit_on(&cur_idx);
			if (player == cur_idx.player)
			{
				++(*player_count);
			}
			else if (player == CHANGE_PLAYER(cur_idx.player))
			{
				++(*opp_count);
			}
			else {} //bit is off

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
	direction_t t_dir = DIRECTIONS[dir];
	count_direction(board,*cur_idx,&t_dir,player_count,opp_count);

	t_dir.brd_dir = -t_dir.brd_dir;
	t_dir.row_dir = -t_dir.row_dir;
	t_dir.col_dir = -t_dir.col_dir;
	count_direction(board,*cur_idx,&t_dir,player_count,opp_count);
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

		if (dir_conditions(move,board->get_num_of_boards(),board->get_board_dim(),static_cast<direction_e>(dir)))
		{
			apply_direction_count(board,move,(direction_e)dir,&player_count,&opp_count);

			//Exclusive OR(A,B) = (!A AND B) OR (A AND !B)
			//Lines occupied by both player's pieces are obsolete\redundant
			if ((player_count != 0 && opp_count == 0) || (player_count == 0 && opp_count != 0))
			{
				if (opp_count == static_cast<direction_e>(board->get_board_dim()) - 1)
				{
					if (player_lines[opp_count] == 0)
					{
						++opp_lines[opp_count];
						++player_lines[player_count];
					}
				}
				else
				{
					++player_lines[player_count];
					++opp_lines[opp_count];
				}
			}
		}
	}

	to_return += player_lines[0] - opp_lines[0];
	for (int i = 1; i < static_cast<int>(board->get_board_dim()); ++i)
	{
		to_return += pow10(second_power) * (player_lines[i] - opp_lines[i]);
		second_power *= 2;
	}

	return to_return;
}

double Minimax::apply_minimax(struct _node_data_t* node, double alpha, double beta, int depth, Minimax::minimax_type_e type)
{
	double to_return;
	bool truncate = false;

	if (depth == 0 || node->current->get_game_state() != VIC_CONT)
	{
		to_return = node->value;
	}
	else
	{
		std::list<move_t>::iterator it = node->unex_children->begin();

		while (it != node->unex_children->end() && !truncate)
		{
			generate_child(node);
			double value = apply_minimax(node->last_child,alpha,beta,depth - 1, CHANGE_MINIMAX_TYPE(type));

			if (value > alpha && type == MAXIMIZE)
			{
				alpha = value;
				cpy_move(&node->last_child->move_played,&node->best_move);
			}
			if (value < beta && type == MINIMIZE)
			{
				beta = value;
				cpy_move(&node->last_child->move_played,&node->best_move);
			}
			if (((alpha >= beta) && (type == MAXIMIZE)) || ((beta <= alpha) && (type == MINIMIZE)))
			{
				truncate = true;
			}

			it = node->unex_children->begin();
		}

		if (type == MAXIMIZE)
		{
			to_return = alpha;
		}
		else
		{
			to_return = beta;
		}
	}

	return to_return;
}

void Minimax::log_test(struct _node_data_t* node, int ply_lvl, double data, minimax_log_type_e type, bool log)
{
	if (log)
	{
		std::cout << "For ply lvl " << ply_lvl << std::endl;
		std::cout << player_string(node->move_played.player) << std::endl;
		std::cout << "Board " << node->move_played.board << std::endl;
		std::cout << "Row " << node->move_played.row << std::endl;
		std::cout << "Column " << node->move_played.col << std::endl;

		switch (type)
		{
			case (LOG_ALPHA):
				std::cout << "maximin alpha value is " << data << std::endl;
				break;

			case (LOG_BETA):
				std::cout << "minimax beta value is " << data << std::endl;
				break;

			case (LOG_PRUNE_ALPHA):
				std::cout << "maximin prune alpha value is " << data << std::endl;
				break;

			case (LOG_PRUNE_BETA):
				std::cout << "minimax prune beta value is " << data << std::endl;
				break;

			case (LOG_MINIMAX_NODE_VALUE):
				std::cout << "minimax node value is " << data << std::endl;
				break;

			case (LOG_MAXIMIN_NODE_VALUE):
				std::cout << "maximin node value is " << data << std::endl;
				break;

			case (LOG_MAXIMIN_VALUE):
				std::cout << "maximin value is " << data << std::endl;
				break;

			case (LOG_MINIMAX_VALUE):
				std::cout << "minimax value is " << data << std::endl;
				break;

			default:
				std::cout << "???" << std::endl;
				break;
		}
	}
}
