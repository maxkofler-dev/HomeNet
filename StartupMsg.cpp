#include "StartupMsg.h"

StartupMsg::StartupMsg(string warningpath)
{
	this->path = warningpath;
}

void StartupMsg::putWarning(int level, string text)
{
	warningsList.open(path, ios::app);
	warningsList << "<" << level << ">" << "<" << text << ">" << endl;
	warningsList.close();
}

void StartupMsg::clear()
{
	warningsList.open(path, ios::out);
	warningsList.close();
}