#include"crypt.h"

using namespace std;

char list[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZÆØÅabcdefghijklmnopqrstuvwxyzæøå1234567890 +-;:,.<>*^!#¤%&/()=?"};
char list2[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZÆØÅabcdefghijklmnopqrstuvwxyzæøå1234567890"};
int listLenght = strlen(list);
int listLenght2 = strlen(list2);
int preKeys[] = {21,13,8,5,3,2,1,1,0};
int preLenght = 9;

string enCrypt(string encryptThis){
	string newString;
	int placement;
	int displacement;
	int newPlace;

	for(int i = 0; i < encryptThis.length(); i++){
		placement = findNumber(encryptThis.at(i));
		displacement = preKeys[i % 9];
		newPlace = (placement + displacement) % 97;

		newString.push_back(list[newPlace]);
	}
	return newString;
}

string deCrypt(string decryptThis){
	string newString;
	int placement;
	int displacement;
	int newPlace;

	for(int i = 0; i < decryptThis.length(); i++){
		placement = findNumber(decryptThis.at(i));
		displacement = preKeys[i % 9];
		newPlace = (placement - displacement) % 97;

		newString.push_back(list[newPlace]);
	}
	return newString;
}

int findNumber(char x){
	for(int i = 0; i < listLenght; i++){
		if(x == list[i]){
			return i;
		}
	}
	return 0;
}

string fileNameEnCrypt(string encryptThis){
	string newString;
	int placement;
	int displacement;
	int newPlace;

	for(int i = 0; i < encryptThis.length(); i++){
		placement = findNumber(encryptThis.at(i));
		displacement = preKeys[i % 9];
		newPlace = (placement + displacement) % 75;

		newString.push_back(list2[newPlace]);
	}
	return newString;
}

string fileNameDeCrypt(string decryptThis){
	string newString;
	int placement;
	int displacement;
	int newPlace;

	for(int i = 0; i < decryptThis.length(); i++){
		placement = findNumber(decryptThis.at(i));
		displacement = preKeys[i % 9];
		newPlace = (placement - displacement) % 75;

		newString.push_back(list2[newPlace]);
	}
	return newString;
}