/*
 * GameUI.cpp
 *
 *  Created on: Jan 12, 2011
 *      Author: freifeldroyi
 */
#include "../../hpp/UI_utils/GameUI.hpp"

#include <iostream>

/*public*/
GameUI::GameUI()
{
	_cont = new UIController();
}

GameUI::~GameUI()
{
	delete _cont;
}

void GameUI::game_start()
{
	menu_input_e inp;
	show_welcome_screen();

	do
	{
		show_menu();
		inp = get_menu_input();

		if (inp != MENU_ERROR)
			do_menu_input(inp);
		else
			std::cout << "Unknown command number. Try again!\n" << std::endl;
	} while (inp != MENU_EXIT);
}

/*private*/
void GameUI::show_welcome_screen()
{
	std::cout << "Welcome to Multi-Dim-Tic Tac Toe!\nCreated by Freifeld Royi as part of Search AI course final project\n" << std::endl;
}

void GameUI::show_about_screen()
{
	std::cout << "This game was created by Freifeld Royi\n"
			"as part of AI search methods class in Ben Gurion University of the Negev, Israel\n"
			"All rights reserved to him\n"
			"Course instructor is Dr. Ariel Felner\n" << std::endl;
}

void GameUI::show_menu()
{
	std::cout << "Main Menu:" << std::endl;
	std::cout << "----------" << std::endl;
	std::cout << "1. 1P vs Comp" << std::endl;
	std::cout << "2. 1P vs 2P" << std::endl;
	std::cout << "3. Comp vs Comp" << std::endl;
	std::cout << "4. About" << std::endl;
	std::cout << "5. Exit\n" << std::endl;
}

menu_input_e GameUI::get_menu_input()
{
	menu_input_e to_return;
	int input;
	std::cin >> input;

	if (input > 0 && input <= 5)
		to_return = static_cast<menu_input_e>(input); // TODO so god damn ugly...
	else
		to_return = MENU_ERROR;

	return to_return;
}

void GameUI::do_menu_input(menu_input_e inp)
{
	switch (inp)
	{
		case MENU_HUM_VS_COMP:
			_cont->play_1P_VS_COMP();
			break;

		case MENU_HUM_VS_HUM:
			_cont->play_1P_VS_2P();
			break;

		case MENU_COMP_VS_COMP:
			_cont->play_COMP_VS_COMP();
			break;

		case MENU_ABOUT:
			show_about_screen();
			break;

		case MENU_EXIT:
			break;

		default:
			break;
	}
}
