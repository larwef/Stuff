#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include "snake.h"

static volatile int keepRunning = 1;

// Getchar screws with ctrl-c. This makes sure you can exit using ctrl-c.
void intHandler(int dummy) {
	keepRunning = 0;
	printf("Program stopped\n");
}

int main() {
	signal(SIGINT, intHandler);

	char board[HEIGHT][WIDTH];
	initBoard(board);
	placeApple(board);

	struct Snake snake1;
	initSnake(&snake1, 5, 5, 5, 4);

	struct Snake snake2;
	initSnake(&snake2, 15, 5, 15, 6);

	moveSnake(board, &snake1, ' ');
	moveSnake(board, &snake2, ' ');
	//printSnake(snake1);
	//printSnake(snake2);
	printBoard(board);

	while (keepRunning && (snake1.alive || snake2.alive)) {
		char dir = getchar();
		if (dir != '\n') {
			printf("Direction: %c", dir);
			printf("\n");
			printf("Score Player 1: %i \t Score Player 2: %i\n", snake1.score, snake2.score);
			moveSnake(board, &snake1, dir);
			moveSnake(board, &snake2, dir);
			//printSnake(snake1);
			//printSnake(snake2);
			printBoard(board);
			printf("\n");
		}
	}
	printf("Game over\n");
}