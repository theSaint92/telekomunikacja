#pragma once
#include "Matrix.h"
#include <string>
#include <exception>

using namespace std;

enum TypeOfMessage {
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

	void messageToBinary();
	void codeBinary1();
	void codeBinary2();
	TypeOfMessage checkTypeOfMessage();
	void decodeBinary();
};
