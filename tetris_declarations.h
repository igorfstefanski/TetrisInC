#ifndef TETRIS_DECLARATIONS_H
#define TETRIS_DECLARATIONS_H

#include <stdbool.h>

#define DELAY   5
#define WAIT_TIME   500
#define ROWS    20
#define COLUMNS 10
#define BLOCK_SIDE_LENGTH   16
#define BORDER_WIDTH    5
#define SCORE_FOR_PIECE 10
#define SCORE_FOR_LINE  100

#define LEFT_BORDER_X   gfx_screenWidth() / 2 - (COLUMNS * BLOCK_SIDE_LENGTH / 2)
#define RIGHT_BORDER_X  gfx_screenWidth() / 2 + (COLUMNS * BLOCK_SIDE_LENGTH / 2)
#define BORDER_TOP_Y    gfx_screenHeight() - (ROWS * BLOCK_SIDE_LENGTH)
#define START_X LEFT_BORDER_X - BLOCK_SIDE_LENGTH
#define START_Y BORDER_TOP_Y - 4 * BLOCK_SIDE_LENGTH

typedef struct
{
	int indexX;
	int indexY;
} block;

typedef struct
{
	block pointOfRotation;
	block a;
	block b;
	block c;
} piece;

enum move { Left, Right, Down, Rotate };

extern char pieces[7/* kind */][4/* rotation */][4][4];
extern int gameBoard[ROWS + 5][COLUMNS + 2];
extern piece tetrominoes[7/* kind */][4/* rotation */];
extern piece currentTetromino[4/* rotation */];
extern piece nextTetromino;
extern int rotation;
extern bool isCurrentTetrominoActive;
extern int score;
extern int currentKind;

void makeTetrominoes();
void makeBoard();

void getCurrentTetromino(int kind);
void getNextTetromino(int kind);

void substractOnIndex();
void addOnIndex();
void moveIndex(enum move whatMove, int howMuch);

void action(bool* pIsRunning, int* pKeyPressed);
bool isPossibleMove(enum move whatMove);
void checkLeftRightBoundaries();
void checkDownBoundary();
void moveLeft();
void moveRight();
void moveDown();
void moveUp();
void iPieceOffset();
void rotate();

void freezeCurrentTetromino();
void searchFullLine();
void clearFullLine(int fullLineIndex);
bool isLineEmpty(int lineIndex);
void moveLinesDown(int lineIndex);

bool isGameOver();
void gameOver(bool* pIsRunning);

void drawScene();
void drawCurrentTetromino();
void drawNextTetromino();
void drawHelpText();
void drawScoreboard();
void drawGameOverText();

#endif
