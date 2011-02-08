/*
 * Minimax.hpp
 *
 *  Created on: Feb 8, 2011
 *      Author: freifeldroyi
 */

#ifndef MINIMAX_HPP_
#define MINIMAX_HPP_

#include "../data_structures/Boards.hpp"
#include "../util/AI_types.hpp"

class Minimax
{
	struct _tree_node_t
	{
		Boards* current; //current board state
		double value;

		struct _tree_node_t* father;
		struct _tree_node_t* next_brother;
		struct _tree_node_t* ex_children; //expanded children array

		move_t* unex_children; //unexpanded
		move_t* best_move; //the best move returned by the recursion

		//NOTE: number of children will be the number of empty slots in current
	} tree_node_t;

	private:
		int _num_of_ply; // holds the number of steps that the minimax tree needs to look ahead
		direction_t* _directions;

		/**
		 * creates a single node of the tree
		 * /param brd - the state of the board
		 */
		struct _tree_node_t* create_tree_node(Boards* brd);

		/**
		 * counts elements according to
		 * current location and direction given as parameters
		 *
		 * /param cur_idx - the index of the current location
		 * /param dir - the direction to count
		 * /param player_count - output parameter
		 * /param opp_count - output parameter
		 */
		void count_direction(Boards* board,
				move_t cur_idx,
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
		void apply_direction_count(Boards* board,
				move_t* cur_idx,
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
		bool dir_conditions(Boards* board, move_t* move, direction_e dir) const;

		/**
		 * calculates the new static heuristic value after
		 * the move given as a parameter
		 */
		double calc_hueristic(Boards* board, move_t* move);

	public:
		Minimax(int num_of_ply = 4);
		~Minimax();

		void set_num_of_ply(int nop);

		move_t* best_move(Boards* cur_brd, player_e pl);
};

#endif /* MINIMAX_HPP_ */
