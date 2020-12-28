#include "ExceptionClass.h"
void ExceptionClass::setECC(string ec)
{
	isDetail = false;
	if (msg != NULL)
	{
		msg->putWarning(0, ec);
	}
	errorCode = ec;
}

void ExceptionClass::setECCwDetail(string ec, string detail)
{
	isDetail = true;
	if (msg != NULL)
	{
		msg->putWarning(0, ec + "(" + detail + ")");
	}
	this->errorCode = ec;
	this->details = detail;
}

string ExceptionClass::getEC()
{
	if (isDetail)
	{
		return errorCode + "(" + details + ")";
	}
	else
	{
		return errorCode;
	}
}

void ExceptionClass::setup(string path)
{
	msg = new StartupMsg(path);
}

void ExceptionClass::printExceptionText()
{
	cout << "Fatal error \"" << errorCode << "\" !!!" << endl;
}