/**er
 * This header files contains some type definitions and basic operations needed for my project
 */

#ifndef TIC_TAC_TOE_TYPES_HPP
#define TIC_TAC_TOE_TYPES_HPP

#define LSB_ONE 1
#define LSB_ZERO 254

enum player_e
{
	O_PLAYER = 0,
	X_PLAYER = 1,

	NUM_OF_PLAYERS = 2
};

#define CHANGE_PLAYER(player) static_cast<player_e>((1 - (player)))

#define BIT_ON 1
#define BIT_OFF 0

#define STRING_ONE "1"
#define STRING_ZERO "0"

/* types and simple operations*/
typedef unsigned char BYTE;
#define BYTE_SIZE (sizeof(BYTE) * 8)

enum move_err_e
{
	ERR_OK = 0, //move was ok
	ERR_START = 1, //game wasn't initialized
	ERR_BOARD = 2, //board input was wrong
	ERR_ROW = 4, //row input was wrong
	ERR_COL = 8, //col input was wrong
	ERR_MOVE_ILLEGAL = 16 //move illegal - place already taken
};

typedef unsigned err_composition;

enum victory_e
{
	VIC_X, //X player has won
	VIC_O, //O player has won
	VIC_DRAW, //all board is full but no winner
	VIC_CONT //continue playing
};

/* represents a move made by a player
 * will be used to keep track of all moves that were done during the game
 * maybe for 'undo' also
 */
typedef struct _move_t
{
	player_e player;
	unsigned board;
	unsigned row;
	unsigned col;
} move_t;

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

/* logic operations */
#define and_op(num1,num2) ((num1) & (num2))
#define or_op(num1,num2) ((num1) | (num2))
#define bitwise_not(num) (~(num))

#endif //TIC_TAC_TOE_TYPES_HPP
