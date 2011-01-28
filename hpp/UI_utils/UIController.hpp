/*
 * UIController.hpp
 *
 *  Created on: Jan 12, 2011
 *      Author: freifeldroyi
 */
#ifndef UICONTROLLER_HPP
#define UICONTROLLER_HPP

#include <list>

#include "../data_structures/Boards.hpp"
#include "../AI_planning/HumanStrategy.hpp"

using namespace std;

class UIController
{
	private:
		Boards* _boards;
		list<move_t>* _moves; //moves

		/**
		 * resets data structures
		 * deletes _boards entirely
		 * removes all elements from _pars
		 *
		 * can be used for new game or destructor
		 */
		void reset();

		/**
		 * Will check basic input correctness. Which means if
		 * row, col and board are in range
		 *
		err_composition check_input(int board, int row, int col);*/

		/**
		 * insert new move to _moves
		 */
		void push_move(unsigned player, unsigned board, unsigned row, unsigned col);

		err_composition set_move(unsigned player, int board,int row, int col);

		/**
		 * checks if the game ended after the last move
		 * /param ply - last move played
		 */
		victory_t is_end(move_t* ply);

		/**
		 * Will apply strategy s untill it's a valid one
		 */
		void try_move(move_t* move, Strategy& s);

		/**
		 * Main "game loop"
		 */
		void play(Strategy& s1, Strategy& s2);

	public:
		UIController();
		~UIController();

		err_composition set_x(int board_num,int row, int col);
		err_composition set_o(int board_num,int row, int col);

		/**
		 * undo the last move
		 */
		void take_back();

		/**
		 * initializes the game boards
		 *
		 * /param board_dim - the dimension of the boards
		 * /param full_game - if true, then full dimensional game will take place
		 *							otherwise only one board will be used
		 */
		void init_game(int board_dim, bool full_game);

		void play_1P_VS_COMP();
		void play_1P_VS_2P();
		void play_COMP_VS_COMP();


		//returns string representation of the boards
		std::string to_string(unsigned scale = 0);
};

#endif //UICONTROLLER_HPP
