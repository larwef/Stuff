package no.wefald.minesweeper;

import java.util.Random;

public class MinesweeperBoard {
    private static final int MAX_WIDTH = 20;
    private static final int MAX_HEIGHT = 20;

    private int width;
    private int height;
    private int mineCount;
    private char[][] mask;
    private int[][] board;

    public int getWidth() {return this.width;}

    public int getHeight() {return this.height;}

    public int getMineCount() {return  this.mineCount;}

    public void initializeBoard() {
        this.height = setBoardWidth();
        this.width = setBoardHeight();
        this.mineCount = setMineCount();

        this.mask = getNewMask(this.width, this.height);
        this.board = getNewBoard(this.width, this.height);

        placeMines(this.mineCount);
    }

    private int setBoardWidth() {
        System.out.print("Input board height(Max " + MAX_HEIGHT + "): ");
        int[][] limits = {{1, MAX_WIDTH}};
        return new LimitedIntInput(1, limits).getLimitedIntInput()[0];
    }

    private int setBoardHeight() {
        System.out.print("Input board width(Max " + MAX_WIDTH + "): ");
        int[][] limits = {{1, MAX_HEIGHT}};
        return new LimitedIntInput(1, limits).getLimitedIntInput()[0];
    }

    private int setMineCount() {
        int maxMines = this.width*this.height;
        System.out.print("Input number of mines(Max " + maxMines +"): ");
        int[][] limits = {{1, maxMines}};
        LimitedIntInput test = new LimitedIntInput(1, limits);
        return test.getLimitedIntInput()[0];
    }

    private char[][] getNewMask(int width, int height) {
        char[][] mask = new char[width][height];

        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                mask[i][j] = '#';
            }
        }
        return mask;
    }

    private int[][] getNewBoard(int width, int height) {
         return new int[width][height];
    }

    private void placeMines(int mineCount) {
        Random rand = new Random();

        int mines_placed = 0;
        int placementX;
        int placementY;

        while(mines_placed < mineCount) {
            placementX = rand.nextInt(this.width);
            placementY = rand.nextInt(this.height);

            if(this.board[placementX][placementY] != 9){
                this.board[placementX][placementY] = 9;
                updateAdjacentTiles(placementX, placementY);
                mines_placed++;
            }
        }
    }

    private void updateAdjacentTiles(int placementX, int placementY) {
        int xLo = (placementX - 1 < 0) ? 0 : placementX - 1;
        int yLo = (placementY - 1 < 0) ? 0 : placementY - 1;
        int xHi = (placementX + 1 >= this.width) ? this.width-1 : placementX + 1;
        int yHi = (placementY + 1 >= this.height) ? this.height-1 : placementY + 1;

        for(int i = xLo; i <= xHi; i++){
            for(int j = yLo; j <= yHi; j++){
                if(this.board[i][j] != 9) {
                    this.board[i][j]++;
                }
            }
        }
    }

    public void updateMask(int xPos, int yPos) {
        if(this.board[xPos][yPos] == 9){
            this.mask[xPos][yPos] = '¤';
        }
        else {
            this.mask[xPos][yPos] = Character.forDigit(board[xPos][yPos], 10);
        }
    }

    public boolean tileNotOpened(int xPos, int yPos) {
        return this.mask[xPos][yPos] == '#';
    }

    public boolean checkForMine(int xPos, int yPos) {
        return (this.board[xPos][yPos] == 9);
    }

    public void revealBoard() {
        for(int i = 0; i < this.width; i++){
            for(int j = 0; j < this.height; j++){
                updateMask(i, j);
            }
        }
        printMask();
    }

    public void printMask() {
        System.out.print("   ");
        for(int i = 0; i < this.width; i++){
            System.out.print(" " + i%10);
        }
        System.out.print("\n  ");
        for(int i = 0; i < 2*this.width + 1; i++){
            System.out.print("-");
        }
        for(int i = 0; i < this.height; i++){
            System.out.print("\n");
            if(i < 10){
                System.out.print(" ");
            }
            System.out.print(i + "| ");
            for(int j = 0; j < this.width; j++){
                System.out.print(mask[j][i] + " ");
            }
        }
        System.out.print("\n\n");
    }
}
