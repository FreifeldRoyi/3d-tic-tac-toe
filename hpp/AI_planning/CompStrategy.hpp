/*
 * CompStrategy.hpp
 *
 *  Created on: Jan 17, 2011
 *      Author: freifeldroyi
 */

#ifndef COMPSTRATEGY_HPP_
#define COMPSTRATEGY_HPP_

#include "Strategy.hpp"
#include "Minimax.hpp"

class CompStrategy : public Strategy
{
	private:
		Minimax _minimax;

	public:
		CompStrategy(Boards* board, player_e player, int look_ahead = 4); //according to assay
		~CompStrategy();

		void print_board();
		void apply_strategy(move_t* move);
};


#endif /* COMPSTRATEGY_HPP_ */
