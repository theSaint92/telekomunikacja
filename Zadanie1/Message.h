#pragma once
#include "Matrix.h"
#include <string>
#include <exception>

using namespace std;

enum TypeOfMessage {
	EMPTY,
	NO_CODING,
	BINARY_FORM,
	ENCODED_FOR_1_ERROR,
	ENCODED_FOR_2_ERRORS
};

class Message
{
	char* fileWithMessage;
	TypeOfMessage typeOfMessage;

	Matrix errorMatrix1;
	Matrix errorMatrix2;

public:
	Message(char* file);
	~Message();

	TypeOfMessage getTypeOfMessage();
	void checkTypeOfMessage();

	void messageToBinary();
	void encodeBinary1();
	void encodeBinary2();
	void decode();
};
