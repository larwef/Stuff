package main

import(
	"fmt"
	"./minesweeper"
)

func main() {
	fmt.Println("Minesweeper");

	var playBoard minesweeper.Board;

	minesweeper.PlayGame(&playBoard);
}