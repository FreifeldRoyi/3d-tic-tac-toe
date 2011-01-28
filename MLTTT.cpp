#include <iostream>

#include "hpp/UI_utils/GameUI.hpp"
#include "hpp/data_structures/Boards.hpp"

int main(int argc, char** argv)
{
	GameUI g_ui;
	g_ui.game_start();
	/*Boards b(3,3);

	std::cout << b.to_string(2000) << std::endl;

	b.set_x(2,2,1);
	b.set_o(2,2,2);
	
	std::cout << b.to_string() << std::endl;*/
}
