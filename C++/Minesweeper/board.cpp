#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "board.h"

using namespace std;

void Board::Initialize() {
	// No check on input should be added
	cout << "Height: ";
	cin >> height;
	cout << "Width: ";
	cin >> width;
	cout << "Number of mines: ";
	cin >> mineCount;

	board = new int*[height];
	mask = new char*[height];

	for(int i = 0; i < height; i++){
		board[i] = new int[width];
		mask[i] = new char[width];
	}

	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			board[i][j] = 0;
			mask[i][j] = '#';
		}
	}
}

void Board::Play() {
	Initialize();
	PlaceMines();
	PrintMask();
	cout << endl;

	int h, w;

	bool lost = false;
	while (!lost) {
		cin >> h >> w;
		lost = OpenField(h, w);
		PrintMask();
	}
	cout << "Game over" << endl;
	RevealBoard();
	PrintMask();
}

void Board::PlaceMines() {
	srand(time(NULL));

	int minesPlaced = 0;

	while (minesPlaced < mineCount) {
		int randH = rand()%(height);
		int randW = rand()%(width);

		if (board[randH][randW] == 9) {
			break;
		}
		else {
			board[randH][randW] = 9;
			minesPlaced++;
		}

		int lowY = randH - 1; 
		int lowX = randW - 1;

		int highY = randH + 1;
		int highX = randW + 1;

		if(randH == 0){
			lowY = 0;
		}
		if(randW == 0){
			lowX = 0;
		}
		if(randH == height){
			lowY = height;
		}
		if(randW == width){
			lowY = width;
		}

		for(int i = lowY; i < highY + 1; i++){
			for(int j = lowX; j < highX + 1; j++){
				if(i == height){
					break;
				}
				if(j == width){
					break;
				}
				if(board[i][j] == 9){
					board[i][j] == 9;
				}
				else{
					board[i][j]++;
				}
			}
		}
	}
}

bool Board::OpenField(int h, int w) {
	// Returns true if player hit a mine
	if (board[h][w] == 9) {
		return true;
	}
	else {
		char i = board[h][w];
		mask[h][w] = '0' + i;
	}
	return false;
}

void Board::RevealBoard() {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			if (board[i][j] == 9) {
				mask[i][j] = 'x';
			}
			else {
				mask[i][j] = '0' + board[i][j];
			}
		}
	}
}

void Board::CleanUp() {
	for (int i = 0; i < height; ++i){
		delete [] board[i];
		delete [] mask[i];
	}
	delete [] board;
	delete [] mask;
}

void Board::PrintMask() {
	cout << "    ";
	for (int i = 0; i < width; ++i) {
		cout << i%10 << " ";
	}
	cout << endl << "  ";
	for (int i = 0; i < 2*width + 1; ++i) {
		cout << "-";
	}
	cout << endl;
	for (int i = 0; i < height; ++i) {
		if (i < 10) {
				cout << " ";
			}
		cout << i << "|" << " ";
		for (int j = 0; j < width; ++j) {
			cout << mask[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
//For debugging
void Board::PrintBoard() {
	for (int i = 0; i < this->height; ++i) {
		cout << endl;
		for (int j = 0; j < this->width; ++j) {
			cout << this->board[i][j] << " ";
		}
	}
	cout << endl;
}