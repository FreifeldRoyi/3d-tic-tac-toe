/**
 * This header files contains some type definitions and basic operations needed for my project
 */

#ifndef TIC_TAC_TOE_TYPES_HPP
#define TIC_TAC_TOE_TYPES_HPP

#define LSB_ONE 1
#define LSB_ZERO 254

#define X_PLAYER 1
#define O_PLAYER 0

#define BIT_ON 1
#define BIT_OFF 0

#define STRING_ONE "1"
#define STRING_ZERO "0"

/* types and simple operations*/
typedef unsigned char BYTE;
#define BYTE_SIZE (sizeof(BYTE) * 8)

enum move_err_t
{
	ERR_OK = 0, //move was ok
	ERR_START = 1, //game wasn't initialized
	ERR_BOARD = 2, //board input was wrong
	ERR_ROW = 4, //row input was wrong
	ERR_COL = 8, //col input was wrong
	ERR_MOVE_ILLEGAL = 16 //move illegal - place already taken
};

typedef unsigned err_composition;

enum victory_t
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
typedef struct _ply_t
{
	unsigned player;
	unsigned board;
	unsigned row;
	unsigned col;
} move_t;

/* logic operations */
#define and_op(num1,num2) (num1 & num2)
#define or_op(num1,num2) (num1 | num2)
#define bitwise_not(num) (~num)

#endif //TIC_TAC_TOE_TYPES_HPP
