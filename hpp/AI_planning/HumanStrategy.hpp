/*
 * HumanStrategy.hpp
 *
 *  Created on: Jan 14, 2011
 *      Author: freifeldroyi
 */

#ifndef HUMANSTRATEGY_HPP_
#define HUMANSTRATEGY_HPP_

#include "Strategy.hpp"

class HumanStrategy : public Strategy
{
	public:
		HumanStrategy(Boards* brd, player_e player);
		~HumanStrategy();

		void print_board();
		void apply_strategy(move_t* move);
};

#endif /* HUMANSTRATEGY_HPP_ */
