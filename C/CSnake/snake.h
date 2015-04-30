static const int HEIGHT = 20;
static const int WIDTH = 40;
static const int MAXSIZE = 50;

// The arrays are define like this because array[MAXSIZE] wasn't allowed
typedef struct Snake{
	int alive;
	int bodx[50];
	int body[50];
	int digest[50];

	int score;
} Snake;

void initBoard(char board[][WIDTH]);
void printBoard(char board[][WIDTH]);
void placeApple(char board[][WIDTH]);

void initSnake(struct Snake* snake, int headx, int heady, int tailx, int taily);
void printSnake(struct Snake snake);
void moveSnake(char board[][WIDTH], struct Snake* snake, char dir);