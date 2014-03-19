#include<iostream>
#include<fstream>
#include<string>
#include <locale.h>

#include"user.h"
#include"filehandler.h"
#include"crypt.h"

using namespace std;


int main(){
	setlocale(LC_ALL, "norwegian");

	ofstream output;
	ifstream input;

	User a("name", "pw");

	cout << "Welcome!" << endl << "Type \"-help\" for help and a list of commands." << endl << endl;

	string command;

	while(command != "-exit"){
		getline(cin, command);

		if(command == "-exit"){
			a.writeToFile(output);
			system("exit");
		}
		else if(command == "-help"){
			cout << endl;
			cout << "-create \"username\" \"password\":  creates a user with the desired password." << endl;
			cout << "-open \"username\":"<<"\t\t"<<"opens a user, you will be asked for a password" << endl;
			cout << "-add \"pwName\" \"pw\":"<<"\t\t"<<"adds a password to a user" << endl;
			cout << "-delete \"pwName\":"<<"\t\t"<<"removes a password from the list" << endl;
			cout << "-print:"<<"\t\t\t\t"<<"prints your passwords to the screen" << endl;
			cout << "-exit:"<<"\t\t\t\t"<<"closes program and saves changes"<< endl << endl;
			cout << "To overwrite a password, use the -add command and use the same pwName again" << endl;
			cout << "NB: Press enter between command, name/passwordname and password" << endl << endl;
		}
		else if(command == "-create"){
			string input;

			cout << "Username: ";
			getline(cin, input);

			a.setName(input);

			cout << "Password: ";
			getline(cin, input);

			a.setPw(input);

			cout << "User " << a.getUserName() << " created." << endl << endl; 
		}
		else if(command == "-add"){
			string name;
			string pw;

			cout << "Name: ";
			getline(cin, name);
			cout << "Password: ";
			getline(cin, pw);

			a.addPw(name, pw);

			cout << "Password for " << name << " added." << endl << endl;
		}
		else if(command == "-delete"){
			string input;

			getline(cin, input);

			a.removePw(input);

			cout << "Entry for " << input << " deleted." << endl << endl;
		}
		else if(command == "-open"){
			string userInput;

			cout << "Username: ";
			getline(cin, userInput);

			a.readFromFile(input, fileNameEnCrypt(userInput));
		}
		else if(command == "-print"){
			a.printPws();
			cout << endl << endl;
		}
	}
}