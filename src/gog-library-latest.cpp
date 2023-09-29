#include <pstream.h>
#include <iostream>
#include <string>
#include <array>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <vector>
#include "headers.h"

using namespace std;

// main
int main()
{
	string allDirectoriesCommand = lsCommand + space + gameInstallersRoot;
	const char *allDirectoriesCharCommand = allDirectoriesCommand.c_str();
	string allDirectoriesStr = execCLI(allDirectoriesCharCommand);

	std::vector<std::string> allDirectories = split(allDirectoriesStr, newlineDelimiter);
	for (int i = 0; i < allDirectories.size(); i++)
	{
		string currentDirectory = allDirectories[i];
		if (currentDirectory.empty())
		{
			continue;
		}
		// std::cout << currentDirectory << std::endl;
		string fullCommand = lsCommand + space + gameInstallersRoot + currentDirectory + gogDir + space + pipeGrepComand;
		const char *fullCharCommand = fullCommand.c_str();

		string foo = execCLI(fullCharCommand);
		std::vector<std::string> installerFiles = split(foo, newlineDelimiter);		
	}
}