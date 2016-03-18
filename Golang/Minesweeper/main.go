package main

import(
	"fmt"
	"./board"
)

func main() {
	fmt.Println("Minesweeper");

	var playBoard board.Board;

	board.PlayGame(&playBoard);
}