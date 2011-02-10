/*
 * Minimax.hpp
 *
 *  Created on: Feb 8, 2011
 *      Author: freifeldroyi
 */

#ifndef MINIMAX_HPP_
#define MINIMAX_HPP_

#include "../data_structures/Boards.hpp"

#include <list>

class Minimax
{
	struct _node_data_t
	{
		Boards* current; //current board state
		double value;

		struct _node_data_t* father;
		struct _node_data_t* brother;
		struct _node_data_t* first_child; //expanded children array
		struct _node_data_t* last_child;
		int num_ex_child;

		std::list<move_t>* unex_children; //unexpanded

		move_t move_played;
		move_t best_move;

		//NOTE: number of children will be the number of empty slots in current
	} node_data_t;

	private:
		int _num_of_ply; // holds the number of steps that the minimax tree needs to look ahead
		player_e _player;
		//direction_t* _directions;
		move_t* _best_moves;
		double _best_val;

		struct _node_data_t* generate_top_node(Boards* board);
		void generate_child(struct _node_data_t* father);
		/**
		 * creates a single node of the tree
		 * /param brd - the state of the board
		 */
		struct _node_data_t* create_tree_node();
		void destroy_tree_node(struct _node_data_t* node);


		/**
		 * counts elements according to
		 * current location and direction given as parameters
		 *
		 * /param cur_idx - the index of the current location
		 * /param dir - the direction to count
		 * /param x_count - output parameter
		 * /param o_count - output parameter
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
		 * /param x_count - output parameter
		 * /param o_count - output parameter
		 */
		void apply_direction_count(Boards* board,
				move_t* cur_idx,
				direction_e dir,
				int* plaer_count,
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
		//bool dir_conditions(Boards* board, move_t* move, direction_e dir) const;

		/**
		 * calculates the new static heuristic value after
		 * the move given as a parameter
		 */
		double calc_hueristic(Boards* board, move_t* move);

		double do_maximin(struct _node_data_t* node, double alpha, double beta, int depth);
		double do_minimax(struct _node_data_t* node, double alpha, double beta, int depth);

		void log_test(struct _node_data_t* node, int ply_lvl, double data, minimax_log_type_e type, bool log = false);

	public:
		Minimax(player_e player, int num_of_ply = 4);
		~Minimax();

		void set_num_of_ply(int nop);

		/**
		 * calculates the best move
		 *
		 * /param cur_brd - the current board state
		 * /param player - the player to make the move
		 * /param move - output parameter
		 */
		void best_move(Boards* cur_brd, player_e player, move_t* move);
};

#endif /* MINIMAX_HPP_ */
