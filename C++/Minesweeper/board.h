#include <vector>

using namespace std;

class Board {
private:
	int width;
	int height;
	int mineCount;
	int** board;
	char** mask;

public:
	void Initialize();
	void Play();
	void PlaceMines();
	bool OpenField(int h, int w);
	void RevealBoard();
	void CleanUp();
	void PrintBoard();
	void PrintMask();
};