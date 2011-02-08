/*
 * Strategy.hpp
 *
 *  Created on: Jan 14, 2011
 *      Author: freifeldroyi
 */

#ifndef STRATEGY_HPP_
#define STRATEGY_HPP_

#include "../data_structures/Boards.hpp"

class Strategy
{
	protected:
		Boards* _board;
		player_e _player;

	public:
		virtual void apply_strategy(move_t* move) = 0;
		virtual void print_board() = 0;
};

#endif /* STRATEGY_HPP_ */
