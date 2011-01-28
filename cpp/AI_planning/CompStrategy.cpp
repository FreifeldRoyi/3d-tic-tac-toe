/*
 * CompStrategy.cpp
 *
 *  Created on: Jan 17, 2011
 *      Author: freifeldroyi
 */

//TODO like duh?!

#include "../../hpp/AI_planning/CompStrategy.hpp"
#include <malloc.h>

CompStrategy::CompStrategy(Boards* board, unsigned player,int look_ahead) : _look_ahead(look_ahead)
{
	_board = board;
	_player = player;
}

CompStrategy::~CompStrategy()
{}

void CompStrategy::apply_strategy(Boards& board, ply_t* ply)
{
	//TODO
}

/*private*/
void build_tree()
{
	//TODO
}

board_tree_t* CompStrategy::generate_tree(Boards* board,
		unsigned look_ahead,
		unsigned player,
		bool is_max)
{
	board_tree_t* to_return = create_tree_node(board);



	return to_return;
}

/*non-class functions*/
board_tree_t* create_tree_node(Boards* brd)
{
	board_tree_t* to_return = (board_tree_t*)malloc(sizeof(board_tree_t));



	return to_return;
}
