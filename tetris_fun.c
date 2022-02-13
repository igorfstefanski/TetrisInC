#include "primlib.h"
#include "tetris_declarations.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

int gameBoard[ROWS + 5][COLUMNS + 2];
piece tetrominoes[7][4];
piece currentTetromino[4];
piece nextTetromino;
int rotation = 0;
bool isCurrentTetrominoActive = false;
int score = 0;
int currentKind = 0;

void makeTetrominoes()
{
	int found1s;

	for (int i = 0; i < 7; i++)
    {
		for (int j = 0; j < 4; j++)
        {
			found1s = 0;
			for (int k = 0; k < 4; k++)
            {
				for (int l = 0; l < 4; l++)
                {
					if (pieces[i][j][k][l] == 0)
                    {
						continue;
					}
                    else if (pieces[i][j][k][l] == 1)
                    {
						switch (found1s++)
                        {
						case 0:
							tetrominoes[i][j].a.indexX = l + 5;
							tetrominoes[i][j].a.indexY = k;
							break;
						case 1:
							tetrominoes[i][j].b.indexX = l + 5;
							tetrominoes[i][j].b.indexY = k;
							break;
						case 2:
							tetrominoes[i][j].c.indexX = l + 5;
							tetrominoes[i][j].c.indexY = k;
							break;
						default:
							break;
						}
					}
                    else if (pieces[i][j][k][l] == 2)
                    {
						tetrominoes[i][j].pointOfRotation.indexX = l + 5;
						tetrominoes[i][j].pointOfRotation.indexY = k;
					}
				}
			}
		}
	}
}

void makeBoard()
{
	for (int i = 0; i < ROWS + 5; i++)
    {
		for (int j = 0; j < COLUMNS + 2; j++)
        {
			if (!j || j == COLUMNS + 1 || i == ROWS + 4)
            {
				gameBoard[i][j] = 3;
			}
            else
            {
				gameBoard[i][j] = 0;
			}
		}
	}
}

void getCurrentTetromino(int kind)
{
	currentTetromino[0] = tetrominoes[kind][0];
	currentTetromino[1] = tetrominoes[kind][1];
	currentTetromino[2] = tetrominoes[kind][2];
	currentTetromino[3] = tetrominoes[kind][3];
	rotation = 0;
    currentKind = kind;

	addOnIndex();
}

void getNextTetromino(int kind) { nextTetromino = tetrominoes[kind][0]; }

void substractOnIndex()
{
	gameBoard[currentTetromino[rotation].pointOfRotation.indexY]
			 [currentTetromino[rotation].pointOfRotation.indexX] -= 2;
	gameBoard[currentTetromino[rotation].a.indexY]
			 [currentTetromino[rotation].a.indexX]--;
	gameBoard[currentTetromino[rotation].b.indexY]
			 [currentTetromino[rotation].b.indexX]--;
	gameBoard[currentTetromino[rotation].c.indexY]
			 [currentTetromino[rotation].c.indexX]--;
}

void addOnIndex()
{
	gameBoard[currentTetromino[rotation].pointOfRotation.indexY]
			 [currentTetromino[rotation].pointOfRotation.indexX] += 2;
	gameBoard[currentTetromino[rotation].a.indexY]
			 [currentTetromino[rotation].a.indexX]++;
	gameBoard[currentTetromino[rotation].b.indexY]
			 [currentTetromino[rotation].b.indexX]++;
	gameBoard[currentTetromino[rotation].c.indexY]
			 [currentTetromino[rotation].c.indexX]++;
}

void moveIndex(enum move whatMove, int howMuch)
{
    switch (whatMove)
    {
        case Left:
            currentTetromino[0].pointOfRotation.indexX -= howMuch;
            currentTetromino[0].a.indexX -= howMuch;
            currentTetromino[0].b.indexX -= howMuch;
            currentTetromino[0].c.indexX -= howMuch;

            currentTetromino[1].pointOfRotation.indexX -= howMuch;
            currentTetromino[1].a.indexX -= howMuch;
            currentTetromino[1].b.indexX -= howMuch;
            currentTetromino[1].c.indexX -= howMuch;

            currentTetromino[2].pointOfRotation.indexX -= howMuch;
            currentTetromino[2].a.indexX -= howMuch;
            currentTetromino[2].b.indexX -= howMuch;
            currentTetromino[2].c.indexX -= howMuch;

            currentTetromino[3].pointOfRotation.indexX -= howMuch;
            currentTetromino[3].a.indexX -= howMuch;
            currentTetromino[3].b.indexX -= howMuch;
            currentTetromino[3].c.indexX -= howMuch;
            break;
        case Right:
            currentTetromino[0].pointOfRotation.indexX += howMuch;
            currentTetromino[0].a.indexX += howMuch;
            currentTetromino[0].b.indexX += howMuch;
            currentTetromino[0].c.indexX += howMuch;

            currentTetromino[1].pointOfRotation.indexX += howMuch;
            currentTetromino[1].a.indexX += howMuch;
            currentTetromino[1].b.indexX += howMuch;
            currentTetromino[1].c.indexX += howMuch;

            currentTetromino[2].pointOfRotation.indexX += howMuch;
            currentTetromino[2].a.indexX += howMuch;
            currentTetromino[2].b.indexX += howMuch;
            currentTetromino[2].c.indexX += howMuch;

            currentTetromino[3].pointOfRotation.indexX += howMuch;
            currentTetromino[3].a.indexX += howMuch;
            currentTetromino[3].b.indexX += howMuch;
            currentTetromino[3].c.indexX += howMuch;
            break;
        case Down:
            currentTetromino[0].pointOfRotation.indexY += howMuch;
            currentTetromino[0].a.indexY += howMuch;
            currentTetromino[0].b.indexY += howMuch;
            currentTetromino[0].c.indexY += howMuch;

            currentTetromino[1].pointOfRotation.indexY += howMuch;
            currentTetromino[1].a.indexY += howMuch;
            currentTetromino[1].b.indexY += howMuch;
            currentTetromino[1].c.indexY += howMuch;

            currentTetromino[2].pointOfRotation.indexY += howMuch;
            currentTetromino[2].a.indexY += howMuch;
            currentTetromino[2].b.indexY += howMuch;
            currentTetromino[2].c.indexY += howMuch;

            currentTetromino[3].pointOfRotation.indexY += howMuch;
            currentTetromino[3].a.indexY += howMuch;
            currentTetromino[3].b.indexY += howMuch;
            currentTetromino[3].c.indexY += howMuch;
            break;
        default:
            break;
    }
}

void action(bool* pIsRunning, int* pKeyPressed)
{
	switch (*pKeyPressed)
    {
        case SDLK_ESCAPE:
            *pIsRunning = false;
            break;
        case SDLK_RIGHT:
            moveRight();
            break;
        case SDLK_LEFT:
            moveLeft();
            break;
        case SDLK_DOWN:
            moveDown();
            break;
        case SDLK_SPACE:
            rotate();
            break;
        default:
            break;
	}
}

bool isPossibleMove(enum move whatMove)
{
	switch (whatMove)
    {
        case Left:
            if (gameBoard[currentTetromino[rotation].a.indexY]
                         [currentTetromino[rotation].a.indexX - 1] > 2 ||
                gameBoard[currentTetromino[rotation].b.indexY]
                         [currentTetromino[rotation].b.indexX - 1] > 2 ||
                gameBoard[currentTetromino[rotation].c.indexY]
                         [currentTetromino[rotation].c.indexX - 1] > 2 ||
                gameBoard[currentTetromino[rotation].pointOfRotation.indexY]
                         [currentTetromino[rotation].pointOfRotation.indexX - 1] > 2)
            {
                return false;
            }
            else
            {
                return true;
            }
            break;
        case Right:
            if (gameBoard[currentTetromino[rotation].a.indexY]
                         [currentTetromino[rotation].a.indexX + 1] > 2 ||
                gameBoard[currentTetromino[rotation].b.indexY]
                         [currentTetromino[rotation].b.indexX + 1] > 2 ||
                gameBoard[currentTetromino[rotation].c.indexY]
                         [currentTetromino[rotation].c.indexX + 1] > 2 ||
                gameBoard[currentTetromino[rotation].pointOfRotation.indexY]
                         [currentTetromino[rotation].pointOfRotation.indexX + 1] > 2)
            {
                return false;
            }
            else
            {
                return true;
            }
            break;
        case Down:
            if (gameBoard[currentTetromino[rotation].a.indexY + 1]
                         [currentTetromino[rotation].a.indexX] > 2 ||
                gameBoard[currentTetromino[rotation].b.indexY + 1]
                         [currentTetromino[rotation].b.indexX] > 2 ||
                gameBoard[currentTetromino[rotation].c.indexY + 1]
                         [currentTetromino[rotation].c.indexX] > 2 ||
                gameBoard[currentTetromino[rotation].pointOfRotation.indexY + 1]
                         [currentTetromino[rotation].pointOfRotation.indexX] > 2)
            {
                freezeCurrentTetromino();
                return false;
            }
            else
            {
                return true;
            }
            break;
        case Rotate:
            if (currentKind == 1)
            {
                if((rotation == 1 && currentTetromino[rotation].pointOfRotation.indexX == 2) || (rotation == 3 && currentTetromino[rotation].pointOfRotation.indexX == COLUMNS - 1))
                {
                    return false;
                }
            }
            if (currentTetromino[rotation].pointOfRotation.indexX == 1 || currentTetromino[rotation].pointOfRotation.indexX == COLUMNS)
            {
                return false;
            }
            else 
            {
                return true;
            }
            break;
        default:
            return false;
            break;
	}
}

void moveLeft()
{
	if (isPossibleMove(Left))
    {
		substractOnIndex();
		moveIndex(Left, 1);
		addOnIndex();
	}
}

void moveRight()
{
	if (isPossibleMove(Right))
    {
		substractOnIndex();
		moveIndex(Right, 1);
		addOnIndex();
	}
}

void moveDown()
{
	if (isPossibleMove(Down))
    {
		substractOnIndex();
		moveIndex(Down, 1);
		addOnIndex();
	}
}

void moveUp()
{
    currentTetromino[0].pointOfRotation.indexY--;
    currentTetromino[0].a.indexY--;
    currentTetromino[0].b.indexY--;
    currentTetromino[0].c.indexY--;

    currentTetromino[1].pointOfRotation.indexY--;
    currentTetromino[1].a.indexY--;
    currentTetromino[1].b.indexY--;
    currentTetromino[1].c.indexY--;

    currentTetromino[2].pointOfRotation.indexY--;
    currentTetromino[2].a.indexY--;
    currentTetromino[2].b.indexY--;
    currentTetromino[2].c.indexY--;

    currentTetromino[3].pointOfRotation.indexY--;
    currentTetromino[3].a.indexY--;
    currentTetromino[3].b.indexY--;
    currentTetromino[3].c.indexY--;
}

void iPieceOffset()
{
    switch (rotation)
    {
        case 0:
            moveIndex(Left, 1);
            moveIndex(Down, 2);
            break;
        case 1:
            moveIndex(Right, 1);
            moveUp();
            break;
        case 2:
            moveIndex(Left, 2);
            moveIndex(Down, 1);
            break;
        case 3:
            moveIndex(Right, 2);
            moveUp();
            moveUp();
            break;
        default:
            break;
    }
}

void rotate()
{
	if (isPossibleMove(Rotate))
    {
        substractOnIndex();

        if (++rotation > 3)
        {
            rotation = 0;
        }
        if(currentKind == 1)
        {
            iPieceOffset();
        }

        addOnIndex();
	}
}

void freezeCurrentTetromino()
{
	gameBoard[currentTetromino[rotation].a.indexY]
			 [currentTetromino[rotation].a.indexX] = 9;
	gameBoard[currentTetromino[rotation].b.indexY]
			 [currentTetromino[rotation].b.indexX] = 9;
	gameBoard[currentTetromino[rotation].c.indexY]
			 [currentTetromino[rotation].c.indexX] = 9;
	gameBoard[currentTetromino[rotation].pointOfRotation.indexY]
			 [currentTetromino[rotation].pointOfRotation.indexX] = 9;
	score += SCORE_FOR_PIECE;

	isCurrentTetrominoActive = false;
}

void searchFullLine()
{
	int found9s;

	for (int i = 4; i < ROWS + 4; i++)
    {
		found9s = 0;
		for (int j = 1; j < COLUMNS + 1; j++)
        {
			if (gameBoard[i][j] == 9)
            {
				found9s++;
			}
		}
		if (found9s == COLUMNS)
        {
			clearFullLine(i);
		}
	}
}

void clearFullLine(int lineIndex)
{
	for (int i = 1; i < COLUMNS + 1; i++)
    {
		gameBoard[lineIndex][i] = 0;
	}
	moveLinesDown(lineIndex);
	score += (SCORE_FOR_LINE - SCORE_FOR_PIECE);
}

bool isLineEmpty(int lineIndex)
{
	for (int i = 1; i < COLUMNS + 1; i++)
    {
		if (gameBoard[lineIndex][i])
        {
			return false;
		}
	}
	return true;
}

void moveLinesDown(int lineIndex)
{
	while (!isLineEmpty(--lineIndex))
    {
		for (int i = 1; i < COLUMNS + 1; i++)
        {
			gameBoard[lineIndex + 1][i] = gameBoard[lineIndex][i];
			gameBoard[lineIndex][i] = 0;
		}
	}
}

bool isGameOver()
{
	for (int i = 1; i < COLUMNS + 1; i++)
    {
		if (gameBoard[3][i] == 9)
        {
			return true;
		}
	}

	return false;
}

void gameOver(bool* pIsRunning)
{
	int key;

	drawGameOverText();
	while (key != SDLK_ESCAPE)
    {
		key = gfx_getkey();
		continue;
	}
	*pIsRunning = false;
}

void drawScene()
{
	gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLACK);

	gfx_filledRect(LEFT_BORDER_X - BORDER_WIDTH, BORDER_TOP_Y, LEFT_BORDER_X,
				   gfx_screenHeight(), GREEN);
	gfx_filledRect(RIGHT_BORDER_X, BORDER_TOP_Y, RIGHT_BORDER_X + BORDER_WIDTH,
				   gfx_screenHeight(), GREEN);

	drawCurrentTetromino();
	drawNextTetromino();
	drawScoreboard();
	drawHelpText();
}

void drawCurrentTetromino()
{
	for (int i = 0; i < ROWS + 4; i++)
    {
		for (int j = 1; j < COLUMNS + 1; j++)
        {
			if (gameBoard[i][j] == 1)
            {
				gfx_filledRect(
					START_X + j * BLOCK_SIDE_LENGTH,
					START_Y + i * BLOCK_SIDE_LENGTH,
					START_X + j * BLOCK_SIDE_LENGTH + BLOCK_SIDE_LENGTH,
					START_Y + i * BLOCK_SIDE_LENGTH + BLOCK_SIDE_LENGTH,
					YELLOW);
			}
            else if (gameBoard[i][j] == 2)
            {
				gfx_filledRect(
					START_X + j * BLOCK_SIDE_LENGTH,
					START_Y + i * BLOCK_SIDE_LENGTH,
					START_X + j * BLOCK_SIDE_LENGTH + BLOCK_SIDE_LENGTH,
					START_Y + i * BLOCK_SIDE_LENGTH + BLOCK_SIDE_LENGTH, RED);
			}
            else if (gameBoard[i][j] == 9)
            {
				gfx_filledRect(
					START_X + j * BLOCK_SIDE_LENGTH,
					START_Y + i * BLOCK_SIDE_LENGTH,
					START_X + j * BLOCK_SIDE_LENGTH + BLOCK_SIDE_LENGTH,
					START_Y + i * BLOCK_SIDE_LENGTH + BLOCK_SIDE_LENGTH, WHITE);
			}
		}
	}
}

void drawNextTetromino()
{
	gfx_filledRect(
		RIGHT_BORDER_X + (nextTetromino.pointOfRotation.indexX + COLUMNS / 4) *
							 BLOCK_SIDE_LENGTH,
		START_Y + nextTetromino.pointOfRotation.indexY * BLOCK_SIDE_LENGTH,
		RIGHT_BORDER_X +
			(nextTetromino.pointOfRotation.indexX + COLUMNS / 4) *
				BLOCK_SIDE_LENGTH +
			BLOCK_SIDE_LENGTH,
		START_Y + nextTetromino.pointOfRotation.indexY * BLOCK_SIDE_LENGTH +
			BLOCK_SIDE_LENGTH,
		RED);
	gfx_filledRect(RIGHT_BORDER_X + (nextTetromino.a.indexX + COLUMNS / 4) *
										BLOCK_SIDE_LENGTH,
				   START_Y + nextTetromino.a.indexY * BLOCK_SIDE_LENGTH,
				   RIGHT_BORDER_X +
					   (nextTetromino.a.indexX + COLUMNS / 4) *
						   BLOCK_SIDE_LENGTH +
					   BLOCK_SIDE_LENGTH,
				   START_Y + nextTetromino.a.indexY * BLOCK_SIDE_LENGTH +
					   BLOCK_SIDE_LENGTH,
				   YELLOW);
	gfx_filledRect(RIGHT_BORDER_X + (nextTetromino.b.indexX + COLUMNS / 4) *
										BLOCK_SIDE_LENGTH,
				   START_Y + nextTetromino.b.indexY * BLOCK_SIDE_LENGTH,
				   RIGHT_BORDER_X +
					   (nextTetromino.b.indexX + COLUMNS / 4) *
						   BLOCK_SIDE_LENGTH +
					   BLOCK_SIDE_LENGTH,
				   START_Y + nextTetromino.b.indexY * BLOCK_SIDE_LENGTH +
					   BLOCK_SIDE_LENGTH,
				   YELLOW);
	gfx_filledRect(RIGHT_BORDER_X + (nextTetromino.c.indexX + COLUMNS / 4) *
										BLOCK_SIDE_LENGTH,
				   START_Y + nextTetromino.c.indexY * BLOCK_SIDE_LENGTH,
				   RIGHT_BORDER_X +
					   (nextTetromino.c.indexX + COLUMNS / 4) *
						   BLOCK_SIDE_LENGTH +
					   BLOCK_SIDE_LENGTH,
				   START_Y + nextTetromino.c.indexY * BLOCK_SIDE_LENGTH +
					   BLOCK_SIDE_LENGTH,
				   YELLOW);
}

void drawHelpText() { gfx_textout(0, 0, "QUIT - ESC", WHITE); }

void drawScoreboard()
{
	char stringScore[100];
	sprintf(stringScore, "%d", score);
	gfx_textout(START_X - 8 * BLOCK_SIDE_LENGTH, START_Y, "Score: ", WHITE);
	gfx_textout(START_X - 4 * BLOCK_SIDE_LENGTH, START_Y, stringScore, WHITE);
}

void drawGameOverText()
{
	drawScene();
	gfx_textout(gfx_screenWidth() / 2, 100, "Game Over!", RED);

	gfx_updateScreen();
	SDL_Delay(DELAY);
}
