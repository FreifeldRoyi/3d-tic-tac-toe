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
		HumanStrategy(Boards* brd, unsigned player);
		~HumanStrategy();

		void print_board();
		move_t apply_strategy();
};

#endif /* HUMANSTRATEGY_HPP_ */
