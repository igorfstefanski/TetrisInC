/*
 * TITLE:   TETRIS IN C
 * AUTHOR:  Igor Stefański
 * DATE: April 2020
 * DESCRIPTION:
 * The aim of the exercise was to write a well-known Tetris game,
 * using simple graphics library which is based on basic primitives from
 * the SDL_gfx library.
 * 
 * Task was introduced on Programming & Data Structures course.
 * 2019/2020 Academic Year
 * Technical University of Lodz, Computer Science
 */
 
#include "primlib.h"
#include "tetris_declarations.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	srand(time(0));

	bool isRunning = true;

	int keyPressed, kind = rand() % 7;
	int time1 = SDL_GetTicks(), time2;

	if (gfx_init())
    {
		exit(3);
	}

	makeTetrominoes();
	makeBoard();

	while (isRunning)
    {
		if (!isCurrentTetrominoActive)
        {
			getCurrentTetromino(kind);
			kind = rand() % 7;
			getNextTetromino(kind);
			isCurrentTetrominoActive = true;
		}

		keyPressed = gfx_pollkey();
		action(&isRunning, &keyPressed);

		drawScene();

		gfx_updateScreen();
		SDL_Delay(DELAY);

		time2 = SDL_GetTicks();
		if (time2 - time1 > WAIT_TIME)
        {
			moveDown();
			time1 = SDL_GetTicks();
		}

		searchFullLine();
		if (isGameOver())
        {
			gameOver(&isRunning);
		}
	}

	return 0;
}
