/*
 * UIController.cpp
 *
 *  Created on: Jan 12, 2011
 *      Author: freifeldroyi
 */

//TODO maybe later use this as a Facade to the data structures and create another controller for "game use"

#include "../../hpp/UI_utils/UIController.hpp"
#include <iostream>

/*public*/

UIController::UIController()
{
	_moves = new list<move_t>();
	_boards = NULL;
}

UIController::~UIController()
{
	reset();
	delete _moves;
}

err_composition UIController::set_o(int board_num,int row, int col)
{
	return set_move(O_PLAYER,board_num,row,col);
}

err_composition UIController::set_x(int board_num,int row, int col)
{
	return set_move(X_PLAYER,board_num,row,col);
}

void UIController::take_back()
{
	move_t p = _moves->back();
	_boards->player_move(p.player,p.board,p.row,p.col,true);
	_moves->pop_back(); //calls destructor
}

void UIController::init_game(int board_dim, bool full_game)
{
	reset();
	if (full_game)
		_boards = new Boards(board_dim,board_dim);
	else
		_boards = new Boards(1,board_dim);
}

void UIController::play_1P_VS_COMP()
{
	std::cout << "1P VS Comp feature is not done yet\n" << std::endl;
	//TODO 1P VS COMP
}

void UIController::play_1P_VS_2P()
{
	int dim;
	char full_game;

	do
	{
		std::cout << "please enter board dim where: 2 < dim < 10: ";
		std::cin >> dim;

	} while (dim < 2 || dim > 10);

	do
	{
		std::cout << "do you want a full 3D game? [y/n]: ";
		std::cin >> full_game;

	} while (full_game != 'y' &&
			full_game != 'n' &&
			full_game != 'Y' &&
			full_game != 'N');

	if (full_game == 'y' || full_game == 'Y')
		init_game(dim,true);
	else
		init_game(dim,false);

	HumanStrategy p1(_boards,X_PLAYER);
	HumanStrategy p2(_boards,O_PLAYER);

	play(p1,p2);
}

void UIController::play_COMP_VS_COMP()
{
	std::cout << "COMP VS Comp feature is not done yet\n" << std::endl;
	//TODO COMP VS COMP
}

std::string UIController::to_string(unsigned scale)
{
	return _boards->to_string(scale);
}

/*private*/
void UIController::reset()
{
	if (_boards != NULL)
	{
		delete _boards;
		_boards = NULL;
	}

	_moves->erase(_moves->begin(),_moves->end());
}

void UIController::push_move(unsigned player, unsigned board, unsigned row, unsigned col)
{
	move_t p;

	p.player = player;
	p.board = board;
	p.col = col;
	p.row = row;

	_moves->push_back(p);
}

err_composition UIController::set_move(unsigned player, int board,int row, int col)
{
	err_composition to_return = _boards->player_move(player,board,row,col,false);

	if (to_return == ERR_OK)
		push_move(player,board,row,col);

	return to_return;
}

victory_t UIController::is_end(move_t* ply)
{
	victory_t to_return = VIC_CONT;
	//TODO
	return to_return;
}

void UIController::try_move(move_t* ply, Strategy& s)
{
	err_composition err = ERR_OK;

	do //TODO change code... too ugly
	{
		*ply = s.apply_strategy();

		err = set_move(ply->player, ply->board, ply->row, ply->col);

		if (err != ERR_OK)
			std::cout << "bad move. try again" << std::endl;
	} while (err != ERR_OK);
}

void UIController::play(Strategy& s1, Strategy& s2)
{
	move_t move;

	do
	{
		//TODO not good, needs while(is_end) check after every move
		move.player = X_PLAYER;
		try_move(&move,s1);
		move.player = O_PLAYER;
		try_move(&move, s2);

	} while (is_end(&move) == VIC_CONT);
}
