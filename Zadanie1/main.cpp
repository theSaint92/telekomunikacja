#include <iostream>
#include <bitset>
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
	
	// TERAZ PROGRAM ZBIERAMY PARAMETRY (SPRAWDZAMY TEZ CZY SA DOBRZE WPISANE)
	ExecType execType;
	string filee = argv[3];
	ifstream file(filee.c_str());
	cout << argc;
	if (argc != 3) {
		cout << "Bad format of command. Write Zadanie1.exe --help to get help";
		return 0;
	}
	cout << argc;
	if (argc == 3) {
		cout << "hello!";
		if (!strcmp(argv[2], "--binary") || !strcmp(argv[2], "-b")) {
			execType = CONVERT_TO_BINARY;
		}
		else if (!strcmp(argv[2], "--code1") || !strcmp(argv[2], "-c1")) {
			execType = ENCODE_TO_CODE1;
		}
		else if (!strcmp(argv[2], "--code2") || !strcmp(argv[2], "-c2")) {
			execType = ENCODE_TO_CODE2;
		}
		else if (!strcmp(argv[2], "--decode") || !strcmp(argv[2], "-d")) {
			execType = DECODE;
		}
		else {
			cout << "Invalid 2nd argument. Write Zadanie1.exe --help to get help";
			return 0;
		}
		//JESZCZE TYLKO SPRAWDZIMY CZY PLIK ISTNIEJE
		if (!file.good()) {
			cout << "Such file doesn't exist. Write Zadanie1.exe --help to get help";
			return 0;
		}
	}


	// DOBRA JEDNAK NIE DLA HELPA - To

	Message Zbadaj(argv[3]);

	char c = 'A';

	unsigned long x = c; // Look ma! No cast!

	cout << "The character '" << c << "' has an ASCII code of " << x << endl;

	std::string binary = std::bitset<8>(x).to_string(); //to binary
	std::cout << binary << "\n";

	unsigned long decimal = std::bitset<8>(binary).to_ulong();
	std::cout << decimal << "\n";

	try {
		Zbadaj.messageToBinary();
	}
	catch (exception& error) {
		cout << error.what();
	}

	


	getchar();
	return 0;
}

void displayhelp() {
	cout << "Welcome to Message code and decoder!\n";
	cout << "Format of using this program is: Zadanie1.exe {-b|-c1|-c2|d} filename";
	cout << "List of parameters:\n";
	cout << "\t-h\t--help\t\tDisplay this menu\n";
	cout << "\t-b\t--binary\tConvert Text to binary form which can be used to coding a message\n";
	cout << "\t-c1\t--code1\t\tEncode binary form to encoded form which is resistant to 1 error during transmission\n";
	cout << "\t-c2\t--code2\t\tEncode binary form to encoded form which is resistant to 2 errors during transmission\n";
	cout << "\t-d\t--decode\tDecode coded message to binary form, or binary form to text.";
}