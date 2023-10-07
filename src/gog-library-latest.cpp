#include <algorithm>
#include <sstream>
#include <set>
#include <pstream.h>
#include <iostream>
#include <string>
#include <array>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <vector>
#include <iterator>
#include "headers.h"

using namespace std;
using namespace constants;
using namespace constants::lgogdownloader;
using namespace goglibrarylatest;

// main
int main()
{
	// get all directories in installer root
	string allDirectoriesCommand = lsCommand + space + gameInstallersRoot;
	const char *allDirectoriesCharCommand = allDirectoriesCommand.c_str();
	string allDirectoriesStr = execCLI(allDirectoriesCharCommand);

	// get all directories from console return
	vector<string> allDirectories = split(allDirectoriesStr, newlineDelimiter);

	// iterate over each game directory
	for (size_t gameDirIndex = 20;
		 gameDirIndex < allDirectories.size();
		 gameDirIndex++)
	{
		string currentDirectory = allDirectories[gameDirIndex];
		string currentGame = currentDirectory.substr(0, currentDirectory.size() - 1);
		if (currentDirectory.empty())
		{
			continue;
		}
		// get all installer files in the game directory
		// cout << currentDirectory << endl;
		string currentInstallersCommand = lsCommand + space + gameInstallersRoot + currentDirectory + gogDir + space + pipeGrepComand;
		const char *currentInstallersCharCommand = currentInstallersCommand.c_str();
		vector<string> currentlyDownloadedInstallers = splitCLIresults(currentInstallersCharCommand, newlineDelimiter);

		// get list of files from lgog
		string thisGameCommand = lgogdownladerCommand + space + lgogdownloaderListDetailsArgument + space + lgogdownloaderGameArgument + space + currentGame;
		const char *thisGameCharCommand = thisGameCommand.c_str();
		map<string, string> installerFileNamesFromGOG = parseInstallerFilesFromLgogReturn(splitCLIresults(thisGameCharCommand, newlineDelimiter));

		vector<string> filesToGetFromGOG;
		for (pair<string, string> fn : installerFileNamesFromGOG)
		{
			// check to see if the current file from GOG already exists in the `currentlyDownloadedInstallers` vector
			if (find(currentlyDownloadedInstallers.begin(), currentlyDownloadedInstallers.end(), fn.second) == currentlyDownloadedInstallers.end())
			{
				// if not, filesToGetFromGOG.push_back gamename/fileid
				filesToGetFromGOG.push_back(fn.first);
			}
		}

		// create comma-separated string of {gamename/fileid}s and pass it to the `--download-file` parameter in lgog
		ostringstream oss;
		copy(begin(filesToGetFromGOG), end(filesToGetFromGOG), ostream_iterator<string>(oss, ","));
		string fileDownloadArguments = oss.str();

		for (string existingFile : currentlyDownloadedInstallers)
		{
			// check each `existingFile` to ensure it's on the GOG list.
			//  If so, continue
			//  If not, delete
		}

		// for_each(installerFileNamesFromGOG.begin(), installerFileNamesFromGOG.end(), logthis);
	}
}