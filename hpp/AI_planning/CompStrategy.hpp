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

		void build_tree();

		/**
		 * this function will generate the tree recursively
		 * The minimax algorithm will be merged with the generation to remove memory
		 * problems
		 */
		board_tree_t* generate_tree(Boards* board, unsigned look_ahead, unsigned player, bool is_max);
		void delete_tree(board_tree_t* tree);

	public:
		CompStrategy(Boards* board, unsigned player, int look_ahead = 4); //according to assay
		~CompStrategy();

		void apply_strategy(Boards& board, move_t* ply);
};


#endif /* COMPSTRATEGY_HPP_ */
