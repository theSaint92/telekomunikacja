#include <iostream>
#include <string>
#include <fstream>
#include "Message.h"

using namespace std;

enum ExecType {
	CONVERT_TO_BINARY,
	ENCODE_TO_CODE1,
	ENCODE_TO_CODE2,
	DECODE
};

void displayhelp();

int main(int argc, char* argv[])
{
	// PROGRAM ODPALONY TYLKO DLA HELPA
	if (argc == 1) {
		displayhelp();
		return 0;
	}

	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")) {
			displayhelp();
			return 0;
		}
	}
	
	// TERAZ ZBIERAMY PARAMETRY (SPRAWDZAMY TEZ CZY SA DOBRZE WPISANE)
	if (argc != 3) {
		cout << "Bad format of command. Write Zadanie1.exe --help to get help";
		return 0;
	}

	ExecType execType;
	string f = argv[2];
	ifstream file(f.c_str());

	if (!file.good()) {
		cout << "Such file doesn't exist. Write Zadanie1.exe --help to get help";
		return 0;
	}

	if (argc == 3) {
		if (!strcmp(argv[1], "--binary") || !strcmp(argv[1], "-b")) {
			execType = CONVERT_TO_BINARY;
		}
		else if (!strcmp(argv[1], "--code1") || !strcmp(argv[1], "-c1")) {
			execType = ENCODE_TO_CODE1;
		}
		else if (!strcmp(argv[1], "--code2") || !strcmp(argv[1], "-c2")) {
			execType = ENCODE_TO_CODE2;
		}
		else if (!strcmp(argv[1], "--decode") || !strcmp(argv[1], "-d")) {
			execType = DECODE;
		}
		else {
			cout << "Invalid first argument. Possible arguments are {-b|-c1|-c2|-d}...";
			return 0;
		}
	}

	//JUZ WIEMY CO CHCEMY ZROBIC - NO TO NAJPIERW ZDEFINUJMY KTOREGO TYPU JEST NASZ MESSAGE

	Message myMessage(argv[2]);
	if (myMessage.getTypeOfMessage() == EMPTY) {
		cout << "Wybrany plik jest pusty...";
	}
	else if (execType == CONVERT_TO_BINARY) {
		cout << myMessage.messageToBinary();
	}
	else if (execType == ENCODE_TO_CODE1) {
		cout << myMessage.encodeBinary(1);
	}
	else if (execType == ENCODE_TO_CODE2) {
		cout << myMessage.encodeBinary(2);
	}
	else if (execType == DECODE) {
		cout << myMessage.decode();
	}
	return 0;
}

void displayhelp() {
	cout << "Welcome to Message code and decoder!\n";
	cout << "Format of using this program is: Zadanie1.exe {-b|-c1|-c2|d} filename\n";
	cout << "List of parameters:\n";
	cout << "\t-h\t--help\t\tDisplay this menu\n";
	cout << "\t-b\t--binary\tConvert Text to binary form which can be used to coding a message\n";
	cout << "\t-c1\t--code1\t\tEncode binary form to encoded form which is resistant to 1 error during transmission\n";
	cout << "\t-c2\t--code2\t\tEncode binary form to encoded form which is resistant to 2 errors during transmission\n";
	cout << "\t-d\t--decode\tDecode coded message to binary form, or binary form to text.";
}