/*
 * HumanStrategy.cpp
 *
 *  Created on: Jan 14, 2011
 *      Author: freifeldroyi
 */
#include "../../hpp/AI_planning/HumanStrategy.hpp"
#include <iostream>

HumanStrategy::HumanStrategy(Boards* brd, player_e player)
{
	 _board = brd;
	 _player = player;
}

HumanStrategy::~HumanStrategy() {}

void HumanStrategy::print_board()
{
	std::cout << _board->to_string() << std::endl;
}

void HumanStrategy::apply_strategy(move_t* move)
{
	std::string player_name = player_string(_player);

	move->player = _player;

	std::cout << player_name << " please enter board number [0 to " << _board->get_num_of_boards() - 1 << "]: ";
	std::cin >> move->board;
	std::cout << player_name << " please enter row number [0 to " << _board->get_board_dim() - 1 << "]: ";
	std::cin >> move->row;
	std::cout << player_name << " please enter col number [0 to " << _board->get_board_dim() - 1 << "]: ";
	std::cin >> move->col;
}
