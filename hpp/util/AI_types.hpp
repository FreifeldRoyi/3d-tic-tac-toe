/*
 * AI_util.hpp
 *
 *  Created on: Feb 8, 2011
 *      Author: freifeldroyi
 */

#ifndef AI_UTIL_HPP_
#define AI_UTIL_HPP_

enum player_type_e
{
	PL_MAX, //max player
	PL_MIN //min player
};

typedef struct _direction_t
{
	int brd_dir;
	int row_dir;
	int col_dir;
} direction_t;

enum direction_e
{
	/**
	 * used in order to decide in which direction the
	 * counting progresses where:
	 * SNGL refers to a direction on a single board
	 * MULT refers to a direction crossing several boards
	 * U,D is row-wise oriented
	 * T,B is board-wise oriented
	 * L,R is column-wise oriented
	 */
	DIR_SNGL_ROW = 0,
	DIR_SNGL_COL = 1,
	DIR_SNGL_DIAG_UL_DR = 2,
	DIR_SNGL_DIAG_UR_DL = 3,
	DIR_MULT_ROW_TL_BR = 4,
	DIR_MULT_ROW_TR_BL = 5,
	DIR_MULT_COL_TU_BD = 6,
	DIR_MULT_COL_TD_BU = 7,
	DIR_MULT_DIAG_TUR_BDL = 8,
	DIR_MULT_DIAG_TUL_BDR = 9,
	DIR_MULT_DIAG_TDL_BUR = 10,
	DIR_MULT_DIAG_TDR_BUL = 11,
	DIR_MULT_PIERCE = 12,

	NUMBER_OF_DIRECTIONS
};

#endif /* AI_UTIL_HPP_ */
