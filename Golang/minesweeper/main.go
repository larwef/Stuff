package main

import(
	"fmt"
	"./board"
)

func main() {
	fmt.Println("Minesweeper")

	var playBoard board.Board

	board.Initialize(&playBoard)
	board.PrintBoard(playBoard)
	fmt.Println("\n")
	board.PrintMask(playBoard)
}