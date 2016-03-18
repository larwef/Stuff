package board

import(
	"fmt"
	"os"
	"bufio"
	"strings"
	"strconv"
	"math/rand"
	"time"
)

type Board struct {
	Width int
	Height int
	MineCount int
	Values [][]int
	Mask [][]string
}

func Initialize(playBoard *Board) {
	GetInput(playBoard)

	playBoard.Values = make([][]int, playBoard.Width)
    for i := range playBoard.Values {
        playBoard.Values[i] = make([]int, playBoard.Height)
    }

    playBoard.Mask = make([][]string, playBoard.Width)
    for i := range playBoard.Mask {
        playBoard.Mask[i] = make([]string, playBoard.Height)
    }

    for i := 0; i < playBoard.Height; i++ {
		for j := 0; j < playBoard.Width; j++ {
			playBoard.Mask[j][i] = "#"
		}
	}

    PlaceMines(playBoard)
}

func GetInput(playBoard *Board) {
	var errW error
	var errH error
	var errM error

	fmt.Println("Chose Width, Height and Number of mines separated by space:")
	reader := bufio.NewReader(os.Stdin)

	for{
		input, _ := reader.ReadString('\n')
		input = strings.TrimRight(input, " \t\r\n")
		inputs := strings.Split(input, " ")

		if len(inputs) != 3 {
			fmt.Println("Invalid input. Try again.")
			continue
		}

		playBoard.Width, errW = strconv.Atoi(inputs[0])
		playBoard.Height, errH = strconv.Atoi(inputs[1])
		playBoard.MineCount, errM = strconv.Atoi(inputs[2])

		if errW != nil || errH != nil || errM != nil {
			fmt.Println("Invalid input. Try again.")
			continue
		}
		break
	}
}

func PlaceMines(playBoard *Board) {
	rand.Seed( time.Now().UTC().UnixNano())
	minesPlaced := 0

	for minesPlaced < playBoard.MineCount {
		randW := rand.Int() % playBoard.Width
		randH := rand.Int() % playBoard.Height

		if playBoard.Values[randH][randW] == 0 {
			playBoard.Values[randH][randW] = 9
			minesPlaced++
		}
	}
}

func PrintMask(playBoard Board) {
	fmt.Printf("    ")
	for i := 0; i < playBoard.Width; i++ {
		fmt.Printf("%d", i%10)
		fmt.Printf(" ")
	}
	fmt.Printf("\n  ")
	for i := 0; i < 2*playBoard.Width + 1; i++ {
		fmt.Printf("-")
	}
	for i := 0; i < playBoard.Height; i++ {
		fmt.Printf("\n")
		if i < 10 {
			fmt.Printf(" ")
		}
		fmt.Printf("%d", i)
		fmt.Printf("| ")
		for j := 0; j < playBoard.Width; j++ {
			fmt.Printf(playBoard.Mask[j][i])
			fmt.Printf(" ")	
		}
	}
}
// For debugging
func PrintBoard(playBoard Board) {
	for i := 0; i < playBoard.Height; i++ {
		fmt.Printf("\n")
		for j := 0; j < playBoard.Width; j++ {
			fmt.Printf("%d", playBoard.Values[j][i])
			fmt.Printf(" ")	
		}
	}
}