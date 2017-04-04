#include "Message.h"
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>


Message::Message(char* file)
{
	//INICJALIZUJEMY MACIERZE I OKRESLAMY PLIK MESSAGE'a
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

string Message::messageToBinary() {

	fstream fwm;
	fwm.open(this->fileWithMessage);
	char znak;

	string result;

	while (fwm.get(znak)) {
		unsigned long ascii_code = znak; // Look ma! No cast!
		string binary = bitset<8>(ascii_code).to_string(); //to binary
		result.append(binary);
		if (!fwm.eof()) result.append("\n");
	}

	//OBCINAMY OSTATNI 'ENTER'
	result = result.substr(0, result.size() - 1);

	return result;
}

string Message::encodeBinary(int noOfErrors) {
	fstream fwm;
	fwm.open(this->fileWithMessage);
	string result;

	if ((noOfErrors != 1) && (noOfErrors != 2)) {
		result = "Unable to encode to fix this number of errors!";
	}

	unsigned int numberOfLoops = 0;
	if (noOfErrors == 1) numberOfLoops = 4;
	else if (noOfErrors == 2) numberOfLoops = 9;

	if (this->typeOfMessage == BINARY_FORM) {
		string binary;
		unsigned int added_bit = 0;
		while (!fwm.eof()) {
			getline(fwm, binary);
			result.append(binary);
			//DOBRA MAMY POBRANĄ LINIJKE W  BINARY_FORM - DODAJEMY BITY PARZYSTOSCI
			for (unsigned int i = 0; i < numberOfLoops; i++) {
				for (unsigned int j = 0; j < 8; j++) {
					if (noOfErrors ==1) added_bit += static_cast<unsigned int>(errorMatrix1[i][j]) * static_cast<unsigned int>(binary[j] - '0'); // Dla korekcji jednego bledu
					else if (noOfErrors==2) added_bit += static_cast<unsigned int>(errorMatrix2[i][j]) * static_cast<unsigned int>(binary[j] - '0'); //Dla korekcji 2 bledow
				}
				added_bit %= 2;
				result.append(1,static_cast<char>(added_bit+'0'));
				added_bit = 0;
			}
			result.append("\n");
		}
	}
	else {
		result = "This file is not in binary form so can't be coded!";
	}

	//OBCINAMY OSTATNI 'ENTER'
	result = result.substr(0, result.size() - 1);

	return result;
}

string Message::decode() {
	
	fstream fwm;
	fwm.open(this->fileWithMessage);
	string result;

	// ----------------------------------------------------------------
	// 1 PRZYPADEK - EMPTY MESSAGE
	// ----------------------------------------------------------------
	if (this->typeOfMessage == EMPTY) {
		result = "This is empty file!";
	}

	// ----------------------------------------------------------------
	// 2 PRZYPADEK - WIADMOSC NIE W FORMIE DO DEKODOWANIA
	// ----------------------------------------------------------------
	else if (this->typeOfMessage == NO_CODING) {
		result = "This file isn't in correct form for decoding!";
	}

	// ----------------------------------------------------------------
	// 3 PRZYPADEK - KONWERTUJEMY Z BINARKI DO CZYTELNEJ WIADOMOSCI
	// ----------------------------------------------------------------
	else if (this->typeOfMessage == BINARY_FORM) {
		string binary;
		while (!fwm.eof()) {
			getline(fwm, binary);
			unsigned long decimal = bitset<8>(binary).to_ulong();
			unsigned char c = static_cast<unsigned char>(decimal);
			result.append(1,c);
		}
	}

	// ----------------------------------------------------------------
	// 4 PRZYPADEK - KONWERTUJEMY Z ENCODED_FOR_1_ERROR NA BINARY_FORM
	// ----------------------------------------------------------------
	else if (this->typeOfMessage == ENCODED_FOR_1_ERROR) {
		string binary;
		int multiplyResult[4] = { 0,0,0,0 };
		int intSuma = 0;

		while (!fwm.eof()) {
			getline(fwm, binary);
			
			//WYZNACZAMY NASZ multiplyResult
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 12; j++) {
					multiplyResult[i] += errorMatrix1[i][j] * static_cast<unsigned int>(binary[j] - '0');
				}
				multiplyResult[i] %= 2;
				intSuma += multiplyResult[i];	
			}
			//OK JEZELI intSuma JEST ROWNY 0, TO NASZE SLOWO TO PIERWSZE 8 BITOW TEJ WIADOMOSCI. CZYLI...
			if (intSuma == 0) {
				result.append(binary.substr(0, 8));
				result.append("\n");
			}
			//ALE JEZELI NIE JEST TO COS TRZEBA POPRAWIC! SZUKAMY WIEC GDZIE JEST BLAD I GO KORYGUJEMY
			else {
				int errorSpottedOn = -1;
				for (int i = 0; i < 12; i++) {
					for (int j = 0; j < 4; j++) {
						if (multiplyResult[j] != errorMatrix1[j][i])
							break;
						if (j == 3) errorSpottedOn = i;
					}
					if (errorSpottedOn != -1)
						break;
				}
				//DOBRA! WIEMY GDZIE ERROR PODMIENIAMY GO TERAZ
				if (binary[errorSpottedOn] == '1') binary[errorSpottedOn] = '0';
				else if (binary[errorSpottedOn] == '0') binary[errorSpottedOn] = '1';

				//I WYPISUJEMY SLOWO
				result.append(binary.substr(0, 8));
				result.append("\n");
			}

			
			/*for (int i = 0; i < 4; i++) {
				cout << multiplyResult[i] <<" ";			
			cout << endl;*/

			//ZEROWANIE DLA NASTEPNEGO LOOPA
			intSuma = 0;
			for (int i = 0; i < 4; i++) {
				multiplyResult[i] = 0;
			}
		}

		//OBCINAMY OSTATNI 'ENTER'
		result = result.substr(0, result.size() - 1);
	}

	// ----------------------------------------------------------------
	// 5 PRZYPADEK - KONWERTUJEMY Z ENCODED_FOR_2_ERRORS NA BINARY_FORM
	// ----------------------------------------------------------------
	else if (this->typeOfMessage == ENCODED_FOR_2_ERRORS) {
		string binary;
		int multiplyResult[9] = { 0,0,0,0,0,0,0,0,0 };
		int intSuma = 0;

		while (!fwm.eof()) {
			getline(fwm, binary);

			//WYZNACZAMY NASZ multiplyResult
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 17; j++) {
					multiplyResult[i] += errorMatrix2[i][j] * static_cast<unsigned int>(binary[j] - '0');
				}
				multiplyResult[i] %= 2;
				intSuma += multiplyResult[i];
			}
			//OK JEZELI intSuma JEST ROWNY 0, TO NASZE SLOWO TO PIERWSZE 8 BITOW TEJ WIADOMOSCI. CZYLI...
			if (intSuma == 0) {
				result.append(binary.substr(0, 8));
				result.append("\n");
			}
			//ALE JEZELI NIE JEST TO COS TRZEBA POPRAWIC! SZUKAMY WIEC GDZIE JEST BLAD I GO KORYGUJEMY
			else {
				int errorSpottedOn[2] = { -1,-1 };
				for (int i = 0; i < 17; i++) {
					for (int j = i + 1; j < 17; j++) {
						for (int k = 0; k < 9; k++) {
							//cout << "ANALIZUJEMY: [" << i << "," << j << "] " << multiplyResult[k] << " " << errorMatrix1[k][i] << " " << errorMatrix1[k][j] << " " << (errorMatrix1[k][i] + errorMatrix1[k][j]) % 2 << endl;
							if (multiplyResult[k] != (errorMatrix2[k][i] + errorMatrix2[k][j])%2 )
								break;
							if (k == 8) {
								errorSpottedOn[0] = i;
								errorSpottedOn[1] = j;
							}
						}
						if (errorSpottedOn[0] != -1)
							break;
					}
					if (errorSpottedOn[0] != -1)
						break;
				}
				
				//cout << "ERRORY SPOTTED ON " << errorSpottedOn[0] << " , " << errorSpottedOn[1] << endl;

				//DOBRA! WIEMY GDZIE ERROR PODMIENIAMY GO TERAZ
				for (int i = 0; i < 2; i++) {
					if (binary[errorSpottedOn[i]] == '1') binary[errorSpottedOn[i]] = '0';
					else if (binary[errorSpottedOn[i]] == '0') binary[errorSpottedOn[i]] = '1';
				}

				//I WYPISUJEMY SLOWO
				result.append(binary.substr(0, 8));
				result.append("\n");
			}


			//for (int i = 0; i < 9; i++) {
			//	cout << multiplyResult[i] << " ";
			//}
			//cout << endl;

			//ZEROWANIE DLA NASTEPNEGO LOOPA
			intSuma = 0;
			for (int i = 0; i < 9; i++) {
				multiplyResult[i] = 0;
			}
		}

		//OBCINAMY OSTATNI 'ENTER'
		result = result.substr(0, result.size() - 1);
	}

	return result;
}