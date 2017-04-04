#pragma once
#include <string>

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

	unsigned int errorMatrix1[4][12] = {	{ 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0 }, \
											{ 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0 }, \
											{ 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0 }, \
											{ 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1 } };
	unsigned int errorMatrix2[9][17] = { {0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, \
											{1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, \
											{1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0}, \
											{0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, \
											{1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0}, \
											{0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0}, \
											{1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, \
											{0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0}, \
											{0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1} };

public:
	Message(char* file);
	~Message();

	TypeOfMessage getTypeOfMessage();
	void checkTypeOfMessage();

	string messageToBinary();
	string encodeBinary(int i);
	string decode();
};
