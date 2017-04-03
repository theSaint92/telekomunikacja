#include "Message.h"
#include <iostream>
#include <fstream>
#include <string>
#include <exception>


Message::Message(char* file)
{
	this->errorMatrix1.change("1ErrorMatrix.txt");
	this->errorMatrix2.change("2ErrorMatrix.txt");
	//std::cout << errorMatrix1.toString() << std::endl;
	//std::cout << errorMatrix2.toString() << std::endl;
	this->fileWithMessage = file;
}


Message::~Message()
{
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