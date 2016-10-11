package minesweeper

import(
	"fmt"
	"os"
	"bufio"
	"strings"
	"strconv"
	"math/rand"
	"time"
)

const (
	Playing = iota
	Won
	Lost
)

type Board struct {
	GameState	int
	Width 		int
	Height 		int
	MineCount 	int
	Moves		int
	Values[][]	int
	Mask[][]	string

}

func PlayGame(playBoard *Board){
	Initialize(playBoard);
	// For debugging purposes
	// PrintBoard(*playBoard);
	fmt.Println("\n");
	PrintMask(*playBoard);

	for playBoard.GameState == Playing {
		x,y := GetPlayInput(*playBoard);
		OpenField(x, y, playBoard);
		PrintMask(*playBoard);
	}

	if playBoard.GameState == Won {
		fmt.Println("You won!");
	} else {
		fmt.Println("You lost");
	}
}

func Initialize(playBoard *Board) {
	playBoard.GameState = Playing;
	playBoard.Moves = 0;
	GetInitInput(playBoard);

	playBoard.Values = make([][]int, playBoard.Width);
    for i := range playBoard.Values {
        playBoard.Values[i] = make([]int, playBoard.Height);
    }

    playBoard.Mask = make([][]string, playBoard.Width);
    for i := range playBoard.Mask {
        playBoard.Mask[i] = make([]string, playBoard.Height);
    }

    for i := 0; i < playBoard.Height; i++ {
		for j := 0; j < playBoard.Width; j++ {
			playBoard.Mask[j][i] = "#";
		}
	}

   PlaceMines(playBoard);
}

func GetInitInput(playBoard *Board) {
	var width int;
	var height int;
	var minecount int;
	var errW error;
	var errH error;
	var errM error;

	fmt.Println("Chose Width, Height and Number of mines separated by space (eg. 10 10 2):")
	reader := bufio.NewReader(os.Stdin);

	for{
		input, _ := reader.ReadString('\n');
		input = strings.TrimRight(input, " \t\r\n");
		inputs := strings.Split(input, " ");

		if len(inputs) != 3 {
			fmt.Println("Invalid input. Try again.");
			continue;
		}

		width, errW = strconv.Atoi(inputs[0]);
		height, errH = strconv.Atoi(inputs[1]);
		minecount, errM = strconv.Atoi(inputs[2]);

		if errW != nil || errH != nil || errM != nil {
			fmt.Println("Invalid input. Try again.");
			continue;
		}
		if width <= 0 || height <= 0 || minecount <= 0 {
			fmt.Println("None of the values can be 0 or negative numbers");
			continue
		}
		if minecount > width*height {
			fmt.Println("Too many mines");
		}
		if height < 3 || width < 3 {
			fmt.Println("Please select 3x3 or higher");
		}
		break;
	}
	playBoard.Width = width;
	playBoard.Height = height;
	playBoard.MineCount = minecount;
}

func PlaceMines(playBoard *Board) {
	rand.Seed(time.Now().UTC().UnixNano());
	minesPlaced := 0;

	for minesPlaced < playBoard.MineCount {
		randW := rand.Int() % playBoard.Width;
		randH := rand.Int() % playBoard.Height;

		if playBoard.Values[randW][randH] != 9 {
			playBoard.Values[randW][randH] = 9;
			UpdateAdjcentTiles(randW, randH, playBoard);
			minesPlaced++;
		}
	}
}

func UpdateAdjcentTiles(x int, y int, playBoard *Board) {
	x_low := x-1;
	x_high := x+1
	y_low := y-1;
	y_high := y+1;

	if x_low < 0 {
		x_low = 0;
	}

	if x_high >= playBoard.Width {
		x_high = playBoard.Width-1;
	}

	if y_low < 0 {
		y_low = 0;
	}

	if y_high >= playBoard.Height {
		y_high = playBoard.Height-1;
	}

	for i := x_low; i <= x_high; i++ {
		for j := y_low; j <= y_high; j++ {
			if playBoard.Values[i][j] != 9 {
				playBoard.Values[i][j]++;
			}
		}
	}
}

func GetPlayInput(playBoard Board) (int, int){
	var xCord int;
	var yCord int;
	var errX error;
	var errY error;

	reader := bufio.NewReader(os.Stdin);
	for{
		fmt.Printf("x y: ");
		input, _ := reader.ReadString('\n');
		input = strings.TrimRight(input, " \t\r\n");
		inputs := strings.Split(input, " ");

		if len(inputs) != 2 {
			fmt.Println("Invalid input. Try again.");
			continue;
		}

		xCord, errX = strconv.Atoi(inputs[0]);
		yCord, errY = strconv.Atoi(inputs[1]);

		if errX != nil || errY != nil {
			fmt.Println("Invalid input. Try again.");
			continue;
		}

		if xCord > playBoard.Width-1 || yCord > playBoard.Height-1 || xCord < 0 || yCord < 0 {
			fmt.Println("Input out of bounds");
			continue;
		} 

		break;
	}

	return xCord, yCord;
}

func OpenField(x int, y int, playBoard *Board) {
	if playBoard.Values[x][y] == 9 {
		playBoard.GameState = Lost;
		playBoard.Mask[x][y] = "¤"; 
		return;
	}
	if playBoard.Mask[x][y] == "#"{
		playBoard.Moves++;
	}
	if playBoard.Moves >= (playBoard.Height*playBoard.Width - playBoard.MineCount){
		playBoard.GameState = Won;
	}
	playBoard.Mask[x][y] = strconv.Itoa(playBoard.Values[x][y]);
}

func PrintMask(playBoard Board) {
	fmt.Printf("   ");
	for i := 0; i < playBoard.Width; i++ {
		fmt.Printf(" %d", i%10);
	}
	fmt.Printf("\n  ")
	for i := 0; i < 2*playBoard.Width + 1; i++ {
		fmt.Printf("-");
	}
	for i := 0; i < playBoard.Height; i++ {
		fmt.Printf("\n");
		if i < 10 {
			fmt.Printf(" ");
		}
		fmt.Printf("%d| ", i);
		for j := 0; j < playBoard.Width; j++ {
			fmt.Printf(playBoard.Mask[j][i]);
			fmt.Printf(" ");
		}
	}
	fmt.Printf("\n");
}
// For debugging
func PrintBoard(playBoard Board) {
	for i := 0; i < playBoard.Height; i++ {
		fmt.Printf("\n");
		for j := 0; j < playBoard.Width; j++ {
			fmt.Printf("%d", playBoard.Values[j][i]);
			fmt.Printf(" ");
		}
	}
}