/*
 * UIController.cpp
 *
 *  Created on: Jan 12, 2011
 *      Author: freifeldroyi
 */

//TODO maybe later use this as a Facade to the data structures and create another controller for "game use"

#include "../../hpp/UI_utils/UIController.hpp"
#include <iostream>

#include "../../hpp/AI_planning/CompStrategy.hpp"

/*public*/

UIController::UIController()
{
	_moves = new list<move_t>();
	_boards = NULL;
	_strat_arr[O_PLAYER] = NULL;
	_strat_arr[X_PLAYER] = NULL;
	_game_end = false;
}

UIController::~UIController()
{
	reset();
	delete _moves;
}

/*err_composition UIController::set_o(int board_num,int row, int col)
{
	return set_move(O_PLAYER,board_num,row,col);
}

err_composition UIController::set_x(int board_num,int row, int col)
{
	return set_move(X_PLAYER,board_num,row,col);
}*/

void UIController::take_back()
{
	move_t p = _moves->back();
	_boards->player_move(&p,true);
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

	_strat_arr[O_PLAYER] = new HumanStrategy(_boards,O_PLAYER);
	_strat_arr[X_PLAYER] = new HumanStrategy(_boards,X_PLAYER);

	play();
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

	if (_strat_arr[O_PLAYER] != NULL)
	{
		delete _strat_arr[O_PLAYER];
		_strat_arr[O_PLAYER] = NULL;
	}

	if (_strat_arr[X_PLAYER] != NULL)
	{
		delete _strat_arr[X_PLAYER];
		_strat_arr[X_PLAYER] = NULL;
	}

	_moves->erase(_moves->begin(),_moves->end());
	_game_end = false;
}

void UIController::push_move(move_t* move)
{
	move_t p;

	p.player = move->player;
	p.board = move->board;
	p.col = move->col;
	p.row = move->row;

	_moves->push_back(p);
}

err_composition UIController::set_move(move_t* move)
{
	err_composition to_return = _boards->player_move(move,false);

	if (to_return == ERR_OK)
		push_move(move);

	return to_return;
}

victory_e UIController::is_end()
{
	victory_e to_return = VIC_CONT;

	if (_game_end)
	{
		//TODO check who is the winner
	}

	return to_return;
}

void UIController::try_move(move_t* move)
{
	err_composition err = ERR_OK;

	do
	{
		_strat_arr[move->player]->print_board();

		*move = _strat_arr[move->player]->apply_strategy();

		//TODO delete from here
		CompStrategy s = CompStrategy(_boards,move->player);
		s.apply_strategy(move);
		//TODO end delete

		err = set_move(move);

		_strat_arr[move->player]->print_board();

		if (err != ERR_OK)
			std::cout << "bad move. try again" << std::endl;

	} while (err != ERR_OK);
}

void UIController::play()
{
	move_t move;

	move.player = X_PLAYER;

	do
	{
		try_move(&move);
		move.player = CHANGE_PLAYER(move.player);

	} while (is_end() == VIC_CONT);
}
