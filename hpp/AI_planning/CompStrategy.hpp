/*
 * CompStrategy.hpp
 *
 *  Created on: Jan 17, 2011
 *      Author: freifeldroyi
 */

#ifndef COMPSTRATEGY_HPP_
#define COMPSTRATEGY_HPP_

#include "Strategy.hpp"

typedef struct _board_tree_t
{
	Boards* current; //current state
	struct _board_tree_t* ex_children; //expanded children array
	move_t* unex_children; //unexpanded
	unsigned num_of_children; //number of children
	move_t* best_move; //the best move returned by the recursion
	int value;
} board_tree_t;

/**
 * creates a single node of the tree
 * /param brd - the state of the board
 */
board_tree_t* create_tree_node(Boards* brd);

class CompStrategy : public Strategy
{
	private:
		int _look_ahead; // holds the number of steps that the minimax tree needs to look ahead
		direction_t* _directions;

		void build_tree();

		/**
		 * this function will generate the tree recursively
		 * The minimax algorithm will be merged with the generation to remove memory
		 * problems
		 */
		board_tree_t* generate_tree(Boards* board, unsigned look_ahead, unsigned player, bool is_max);
		void delete_tree(board_tree_t* tree);

		/**
		 * counts elements according to
		 * current location and direction given as parameters
		 *
		 * /param cur_idx - the index of the current location
		 * /param dir - the direction to count
		 * /param player_count - output parameter
		 * /param opp_count - output parameter
		 */
		void count_direction(move_t cur_idx,
				direction_t* dir,
				int* player_count,
				int* opp_count);

		/**
		 * applies counting on the appropriate direction
		 * according to suitable conditions for each direction
		 *
		 * /param cur_idx - the move to make
		 * /param dir - the direction to apply counting on
		 * /param player_count - output parameter
		 * /param opp_count - output parameter
		 */
		void apply_direction_count(move_t* cur_idx,
				direction_e dir,
				int* player_count,
				int* opp_count);

		/**
		 * defines the conditions needed to be true in order for the current
		 * direction is worth checking
		 *
		 * e.g 4x4 board
		 *      _______________
		 *     |___|___|___|___|
		 *     |___|___|___|_x_| <- won't count pieces diagonally
		 *     |___|_x_|___|___| <- count piece diagonally also
		 *     |___|___|___|_x_| <- almost all directions are counted
		 *
		 * /param move - the move played
		 * /param dir - the direction
		 */
		bool dir_conditions(move_t* move, direction_e dir) const;

		/**
		 * calculates the new static heuristic value after
		 * the move given as a parameter
		 */
		double calc_hueristic(move_t* move);

	public:
		CompStrategy(Boards* board, unsigned player, int look_ahead = 4); //according to assay
		~CompStrategy();

		void print_board();
		void apply_strategy(move_t* move);
		move_t apply_strategy();
};


#endif /* COMPSTRATEGY_HPP_ */
