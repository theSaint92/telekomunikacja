#pragma once
#include "Matrix.h"

class Message
{
	static Matrix errorMatrix1 = Matrix("1ErrorMatrix.txt");
	static Matrix* errorMatrix2;


public:
	Message();
	~Message();
};
