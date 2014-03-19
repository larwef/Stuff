#include<time.h>
#include"user.h"

using namespace std;

User::User(string name, string pw){
	this->userName = name;
	this->userPw = pw;
}

void User::setName(string name){
	this->userName = name;
}

void User::setPw(string pw){
	this->userPw = pw;
}

string User::getUserName(){
	return userName;
}

string User::getPw(){
	return userPw;
}

void User::addPw(string label, string pw){
	pws[label] = pw;
}

void User::removePw(string label){
	map<string, string>::iterator it;

	for(it = pws.begin(); it != pws.end(); ++it){
		if(it->first == label){
			pws.erase(it);
			return;
		}
	}
}

void User::printPws(){
	map<string, string>::iterator it;

	for(it = pws.begin(); it != pws.end(); ++it){
		cout << it->first << ": " << it->second << endl;
	}
}