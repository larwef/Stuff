package no.wefald.minesweeper;

public class MinesweeperGame {
    private enum GameState {
        PLAYING,
        LOST,
        WON
    }

    private GameState gameState;
    private MinesweeperBoard gameBoard;
    private int turnsUsed;

    private void welcomeMessage() {
        System.out.println("Welcome to minesweeper!");
    }

    public void playGame(){
        welcomeMessage();
        initializeGame();

        playLoop:
        while(true) {
            switch (this.gameState) {
                case PLAYING:
                    playTurn();
                    break;
                case WON:
                    gameBoard.revealBoard();
                    System.out.println("You won!");
                    break playLoop;
                case LOST:
                    gameBoard.revealBoard();
                    System.out.println("You lost!");
                    break playLoop;
                default:
                    System.out.println("How did we end up here?");
                    break playLoop;
            }
        }
    }

    private void initializeGame() {
        this.gameState = GameState.PLAYING;
        this.turnsUsed = 0;
        this.gameBoard = new MinesweeperBoard();

        this.gameBoard.initializeBoard();
    }

    private void playTurn() {
        gameBoard.printMask();
        System.out.println("Open tile:");

        int[] userInput = getTurnInput();
        int xInput = userInput[0];
        int yInput = userInput[1];

        this.gameState = updateGameState(xInput, yInput);
    }

    public int[] getTurnInput() {
        int[] xLimits = {0, gameBoard.getWidth() - 1};
        int[] yLimits = {0, gameBoard.getHeight() - 1};
        int[][] inputLimits = {xLimits, yLimits};

        return new LimitedIntInput(2, inputLimits).getLimitedIntInput();
    }

    private GameState updateGameState(int xInput, int yInput) {
        gameBoard.updateMask(xInput, yInput);

        if (this.gameBoard.tileNotOpened(xInput, yInput)) {
            this.turnsUsed++;
        }

        if (gameBoard.checkForMine(xInput, yInput)) {
            return GameState.LOST;
        }

        int numberOfSafeTiles = (this.gameBoard.getWidth() * this.gameBoard.getHeight()) - this.gameBoard.getMineCount();
        if (this.turnsUsed >= numberOfSafeTiles) {
            return GameState.WON;
        }

        return GameState.PLAYING;
    }
}
