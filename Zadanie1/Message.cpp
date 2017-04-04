#include "Message.h"
#include <iostream>
#include <fstream>
#include <string>
#include <exception>


Message::Message(char* file)
{
	//INICJALIZUJEMY MACIERZE I OKRESLAMY PLIK MESSAGE'a
	this->errorMatrix1.change("1ErrorMatrix.txt");
	this->errorMatrix2.change("2ErrorMatrix.txt");
	this->fileWithMessage = file;
	this->checkTypeOfMessage();
}


Message::~Message()
{
}

TypeOfMessage Message::getTypeOfMessage() {
	return this->typeOfMessage;
}

void Message::checkTypeOfMessage() {
	//NO I TERAZ SPRAWDZAMY CZYM TAK WLASCIWIE JEST MESSAGE
	fstream fwm;
	fwm.open(this->fileWithMessage);

	//NAJPIERW SPRAWDZMY CZY TO NIE JEST PRZYPADKIEM PUSTY PLIK
	if (fwm.peek() == fstream::traits_type::eof()) {
		this->typeOfMessage = EMPTY;
		return;
	}
	else this->typeOfMessage = NO_CODING;

	//SKORO JUZ WIEMY ZE NIE JEST TO 'EMPTY' TO ZAKLADAMY ZE JEST TO 'NO_CODING'
	//I EWENTUALNIE MOZE NAM SIE UDA POKAZAC ZE JEST INACZEJ
	string temp;
	getline(fwm, temp);
	if (temp.length() > 17) return; //JAK WIEKSZY TO BANKOWO NO_CODING
	for (unsigned int i = 0; i < temp.length(); i++) { //JAK COS POZA 0 i 1 TO TEZ BANKOWO NO_CODING
		if ((temp[i] != '0') && (temp[i] != '1')) return;
	}

	if (temp.length() == 8) {
		//PIERWSZE SLOWO MA DLUGOSC 8 - MOZE TO BEDZIE BINARY_FORM
		while (!fwm.eof()) {
			getline(fwm, temp);
			if (temp.length() != 8) return;
			for (int i = 0; i < 8; i++) {
				if ((temp[i] != '0') && (temp[i] != '1')) return;
			}
		}
		this->typeOfMessage = BINARY_FORM;
	}
	else if (temp.length() == 12) {
		//PIERWSZE SLOWO MA DLUGOSC 12 - MOZE TO BEDZIE ENCODED_FOR_1_ERROR	
		while (!fwm.eof()) {
			getline(fwm, temp);
			if (temp.length() != 12) return;
			for (int i = 0; i < 12; i++) {
				if ((temp[i] != '0') && (temp[i] != '1')) return;
			}
		}
		this->typeOfMessage = ENCODED_FOR_1_ERROR;
	}
	else if (temp.length() == 17) {
		//PIERWSZE SLOWO MA DLUGOSC 17 - MOZE TO BEDZIE ENCODED_FOR_2_ERRORS
		while (!fwm.eof()) {
			getline(fwm, temp);
			if (temp.length() != 17) return;
			for (int i = 0; i < 17; i++) {
				if ((temp[i] != '0') && (temp[i] != '1')) return;
			}
		}
		this->typeOfMessage = ENCODED_FOR_2_ERRORS;
	}
}


void Message::messageToBinary() {
	//if (this->fileWithMessage == NULL) {
	//	throw "Message File not specifed!";
	//	return;
	//}	
	fstream fwm;
	fwm.open(this->fileWithMessage);

	//if (!fwm.is_open())
	//	throw exception;

}