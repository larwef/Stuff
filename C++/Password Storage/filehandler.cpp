#include"filehandler.h"
#include"user.h"
#include"crypt.h"

void User::writeToFile(ofstream& file){
	openFile(file, fileNameEnCrypt(userName));

	file << enCrypt(userPw) << endl;

	map<string, string>::iterator it;

	for(it = pws.begin(); it != pws.end(); ++it){
		file << enCrypt(it->first) << endl << enCrypt(it->second) << endl;
	}
	file.close();
}

void User::readFromFile(ifstream& file, string filename){
	openFile(file, filename);

	this->userName = fileNameDeCrypt(filename);

	string input;
	bool isName = true;
	string name;
	string pw;

	getline(file, input);
	this->userPw = deCrypt(input);

	string guessedPw;
	cout << "Password: ";
	getline(cin, guessedPw);

	if(guessedPw != this->userPw){
		cout << "Wrong password." << endl;
		file.close();
		return;
	}

	while(!file.eof()){
		if(isName == true){
			getline(file, name);
			isName = false;
		}
		else{
			getline(file, pw);
			isName = true;
			addPw(deCrypt(name), deCrypt(pw));
		}
	}
	cout << "User " << this->userName << " loaded." << endl << endl;

	file.close();
}