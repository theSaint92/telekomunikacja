#include "Message.h"
#include <iostream>


Message::Message()
{
	this->errorMatrix1.change("1ErrorMatrix.txt");
	this->errorMatrix2.change("2ErrorMatrix.txt");
	//std::cout << errorMatrix1.toString() << std::endl;
	//std::cout << errorMatrix2.toString() << std::endl;
}


Message::~Message()
{
}
