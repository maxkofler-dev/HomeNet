#ifndef EXCEPTIONCLASS
#define EXCEPTIONCLASS

#include <string>
#include <iostream>

#include "../StartupMsg/StartupMsg.h"

using namespace std;


class ExceptionClass
{
public:
	void setECC(string);
	void setECCwDetail(string, string);
	string getEC();
	void setup(string);

	void printExceptionText();
private:
	string errorCode;
	string details;
	StartupMsg* msg;
	bool isDetail;
};

#include "ExceptionClass.cpp"

#endif
