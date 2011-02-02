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
		unsigned _player;

	public:
		virtual move_t apply_strategy() = 0;
		virtual void print_board() = 0;
};

#endif /* STRATEGY_HPP_ */
