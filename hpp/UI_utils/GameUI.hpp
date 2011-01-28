/*
 * GameUI.hpp
 *
 *  Created on: Jan 12, 2011
 *      Author: freifeldroyi
 */
#ifndef GAMEUI_HPP
#define GAMEUI_HPP

#include "UIController.hpp"

enum menu_input_e
{
	MENU_HUM_VS_COMP = 1,
	MENU_HUM_VS_HUM = 2,
	MENU_COMP_VS_COMP = 3,
	MENU_ABOUT = 4,
	MENU_EXIT = 5,
	MENU_ERROR
};

class GameUI
{
	private:
		UIController* _cont;

		/*Shows the welcoming screen*/
		void show_welcome_screen();

		/*shows the about screen*/
		void show_about_screen();

		/*shows the menu screen*/
		void show_menu();
		menu_input_e get_menu_input();
		void do_menu_input(menu_input_e inp);

	public:
		GameUI();
		~GameUI();

		void game_start();

};

#endif //GAMEUI_HPP
