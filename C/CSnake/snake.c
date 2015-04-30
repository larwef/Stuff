#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "snake.h"

void initBoard(char board[][WIDTH]){
	for (int i = 0; i < HEIGHT; i++){
		for (int j = 0; j < WIDTH; j++){
			board[i][j] = ' ';
		}
	}
}
// This can be rewritten for the framebuffer. Can divide it into blocks
void printBoard(char board[][WIDTH]){
	for (int i = 0; i < WIDTH+2; i++) printf("-");
		printf("\n");
	for (int i = 0; i < HEIGHT; i++){
		printf("|");
		for (int j = 0; j < WIDTH; j++){
			printf("%c", board[i][j]);
		}
		printf("|\n");
	}
	for (int i = 0; i<WIDTH+2; i++) printf("-");
}
// Makes sure the new apple takes a unoccupied space
void placeApple(char board[][WIDTH]){
	int placed = 0;

	while (!placed){
		int x = rand() % WIDTH;
		int y = rand() % HEIGHT;

		if (board[y][x] == ' '){
			board[y][x] = 'x';
			placed = 1;
		}
	}
}
void initSnake(struct Snake* snake, int headx, int heady, int tailx, int taily){
	for (int i = 0; i < MAXSIZE; ++i){
		snake->bodx[i] = -1;
		snake->body[i] = -1;
		snake->digest[i] = 0;
	}
	snake->bodx[0] = headx;
	snake->body[0] = heady;

	snake->bodx[1] = tailx;
	snake->body[1] = taily;

	snake->alive = 1;
	snake->score = 0;
}

void printSnake(struct Snake snake){
	for (int i = 0; i < MAXSIZE; ++i){
		printf("[%i,%i] ", snake.bodx[i], snake.body[i]);
	}
	printf("\n");
	for (int i = 0; i < MAXSIZE; ++i){
		printf("[%i] ", snake.digest[i]);
	}
	printf("\n Score: %i\n", snake.score);
}
// Could be divided into more functions for readability. F.eks. collisionDetection etc.
void moveSnake(char board[][WIDTH], struct Snake* snake, char dir){
	if (!snake->alive || (dir != 'w' && dir != 's' && dir != 'a' && dir != 'd')){
		return;
	}
	int tmpx[MAXSIZE];
	int tmpy[MAXSIZE];
	int tmpd[MAXSIZE];
	// Used to shift values to the right
	tmpx[0] = snake->bodx[0];
	tmpy[0] = snake->body[0];
	tmpd[0] = snake->digest[0];

	for (int i = 0; i < MAXSIZE; ++i){
		// End of the snake
		if (snake->bodx[i] == -1){
			if (snake->digest[i-1] == 1){
				snake->bodx[i] = tmpx[i-1];
				snake->body[i] = tmpy[i-1];
				snake->digest[i-1] = 0;
			}
			break;
		}
		board[snake->body[i]][snake->bodx[i]] = ' ';
		// Takes care of the snakes body
		if (i > 0){
			tmpx[i] = snake->bodx[i];
			tmpy[i] = snake->body[i];
			tmpd[i] = snake->digest[i];
			snake->bodx[i] = tmpx[i-1];
			snake->body[i] = tmpy[i-1];
			snake->digest[i] = tmpd[i-1];
			board[snake->body[i]][snake->bodx[i]] = 'o';
		}
	}
	// Handles the head
	switch (dir){
		case 'w': snake->body[0] -= 1;
			break;
		case 's': snake->body[0] += 1;
			break;
		case 'a': snake->bodx[0] -= 1;
			break;
		case 'd': snake->bodx[0] += 1;
			break;
	}
	// Collision detection
	if (board[snake->body[0]][snake->bodx[0]] == 'o' ||
		board[snake->body[0]][snake->bodx[0]] == 'O' ||
		snake->bodx[0] < 0 || snake->bodx[0] >= WIDTH ||
		snake->body[0] < 0 || snake->body[0] >= HEIGHT ){
		snake->alive = 0;
		return;
	} 
	// Score detection
	if (board[snake->body[0]][snake->bodx[0]] == 'x'){
		snake->score += 1;
		snake->digest[0] = 1;
		placeApple(board);
	}
	else{
		snake->digest[0] = 0;
	}

	board[snake->body[0]][snake->bodx[0]] = 'O';
}