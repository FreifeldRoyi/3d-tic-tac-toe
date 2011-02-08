/*
 * CompStrategy.cpp
 *
 *  Created on: Jan 17, 2011
 *      Author: freifeldroyi
 */
#include "../../hpp/AI_planning/CompStrategy.hpp"
#include <malloc.h>
#include <math.h>

CompStrategy::CompStrategy(Boards* board, player_e player,int look_ahead)
{
	_tree = Minimax(look_ahead);
	_board = board;
	_player = player;
}

CompStrategy::~CompStrategy() {}

void CompStrategy::print_board() {}

void CompStrategy::apply_strategy(move_t* move)
{

}
