#include<iostream>
#include<vector>
#include<string>
#include<map>

using namespace std;

class User{
private:
	string userName;
	string userPw;
	map<string, string> pws;
public:
	User(string name, string pw);
	void setName(string name);
	void setPw(string pw);
	string getUserName();
	string getPw();
	void addPw(string label, string pw);
	void removePw(string label);
	void printPws();

	void writeToFile(ofstream& file);
	void readFromFile(ifstream& file,string filename);
};