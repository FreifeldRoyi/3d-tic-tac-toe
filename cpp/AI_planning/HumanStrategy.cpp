/*
 * HumanStrategy.cpp
 *
 *  Created on: Jan 14, 2011
 *      Author: freifeldroyi
 */
#include "../../hpp/AI_planning/HumanStrategy.hpp"
#include <iostream>

HumanStrategy::HumanStrategy(Boards* brd, unsigned player)
{
	 _board = brd;
	 _player = player;
}

HumanStrategy::~HumanStrategy() {}

move_t HumanStrategy::apply_strategy()
{
	move_t to_return;
	std::string player_name;

	if (_player == X_PLAYER)
		player_name = "X Player";
	else
		player_name = "O Player";

	std::cout << _board->to_string() << std::endl;

	std::cout << player_name << " please enter board number [0 to " << _board->get_num_of_boards() << "]: ";
	std::cin >> to_return.board;
	std::cout << player_name << " please enter row number [0 to " << _board->get_board_dim() << "]: ";
	std::cin >> to_return.row;
	std::cout << player_name << " please enter col number [0 to " << _board->get_board_dim() << "]: ";
	std::cin >> to_return.col;

	std::cout << _board->to_string() << std::endl;


	return to_return;
}
