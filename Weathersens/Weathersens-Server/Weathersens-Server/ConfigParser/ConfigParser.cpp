#include "ConfigParser.h"

void ConfigParser::parseConfig(string path)
{
	ifstream cFile;
	string buffer; 
	int cLines = 0;

	cFile.open(path, ios::in);

	if (cFile.fail())	//Check if file is accessable
	{
		cFile.close();
        exception->setECC("ST-RC-1");
		throw exception;
	}

	//Count the ammount of lines to reserve the memory for string arrays
	while (!cFile.eof())
	{
        if (cFile.fail())	//Check if the file is still fine
        {
            cFile.close();
            exception->setECC("ST-RC-2");
            throw exception;
        }

		getline(cFile, buffer);
		cLines++;
	}

	//Reserve the memory for the arrays to store the information
	configNames = new string[cLines];
	configs = new string[cLines];

    cFile.close();
    cFile.open(path, ios::in);

	if (cFile.fail())	//Check if file is still ok
	{
		cFile.close();
        exception->setECC("ST-RC-2");
		throw exception;
	}


	int posStartName = 0;
	int posEndName = 0;
	int posStartConf = 0;
	int posEndConf = 0;

	int configId = 0;

	while (!cFile.eof())	//Now parse the actual data
	{
		if (cFile.fail())	//Always check if file is readable
		{
			cFile.close();
            exception->setECC("ST-RC-2");
			throw exception;
		}

		getline(cFile, buffer);

		if (buffer.find('#') < buffer.length())	//if a "#" arrives in a line ignore it
		{
			cout << "Ignoring line \"" << buffer << "\" because of found '#'!" << endl;
		}

		else
		{
			//Search for the start & end signs of the configs names and configs
			posStartName = buffer.find('<');
			posEndName = buffer.find('>', posStartName);
			posStartConf = buffer.find('<', posEndName);
			posEndConf = buffer.find('>', posStartConf);

			for (int i = posStartName + 1; i < posEndName; i++)
			{
				configNames[configId] += buffer[i];
			}

			for (int i = posStartConf + 1; i < posEndConf; i++)
			{
				configs[configId] += buffer[i];
			}

			cout << "Config name[" << configId << "] = \"" << configNames[configId] << "\"" << endl;
			cout << "Config[" << configId << "] = \"" << configs[configId] << "\"" << endl;

			configId++;
		}
	}
    configParsed_ = true;
	configsCount = configId;
}

string ConfigParser::getConfig(string configName, bool isCritical, bool throwNonCriticalNotFoundException)
{
	int configPos = 0;
	bool match = false;


	while (configPos < configsCount)	//Search the array of the config Names for a matching name
	{
		if (configNames[configPos] == configName)
		{
			match = true;
			break;
		}
		configPos++;
	}

	if (match)
	{
		return configs[configPos];
	}
	else
	{
		if (isCritical)
		{
			throw CriticalConfigNotFoundException(configName);
		}
		else
		{
			if (throwNonCriticalNotFoundException)
			{
				throw ConfigNotFoundException(configName);
			}
			else
			{
				return NULL;
			}
		}
	}
}

ConfigParser::ConfigParser(ExceptionClass* exc)
{
    exception = exc;
    configParsed_ = false;
}
