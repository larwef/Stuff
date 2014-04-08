#include <iostream>
#include <string>

#include "board.h"

using namespace std;

int main() {
	Board board;

	string command;
	while (command != "exit") {
		board.Play();
		cout << "Type exit to quit, or anything to play again" << endl;
		cin >> command;
	}

	return 0;
}