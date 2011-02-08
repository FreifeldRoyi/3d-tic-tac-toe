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
#include "../AI_planning/CompStrategy.hpp"

class UIController
{
	private:
		Boards* _boards;
		std::list<move_t>* _moves; //moves
		Strategy* _strat_arr[NUM_OF_PLAYERS];
		bool _game_end;

		/**
		 * resets data structures
		 * deletes _boards entirely
		 * removes all elements from _pars
		 *
		 * can be used for new game or destructor
		 */
		void reset();

		/**
		 * insert new move to _moves
		 */
		void push_move(move_t* move);

		err_composition set_move(move_t* move);

		/**
		 * checks if the game ended after the last move
		 */
		victory_e is_end();

		/**
		 * Will apply strategy s until it's a valid one
		 */
		void try_move(move_t* move);//, Strategy& s);

		/**
		 * Main "game loop"
		 */
		void play();//(Strategy& s_O, Strategy& s_X);
		void input_game_settings();
		int input_computer_settings(std::string name = "computer");

	public:
		UIController();
		~UIController();

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
