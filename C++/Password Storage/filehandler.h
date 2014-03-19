#include<fstream>

using namespace std;

template<typename T>
void openFile(T& file, string name){
	name.append(".bin");

	file.open(name);

	if(file.fail()){
		cout << "Error opening file!" << endl;
	}
}