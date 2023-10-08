#include "headers.hpp"
#include <map>
#include <pstream.h>
#include <iostream>
#include <string>
#include <array>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <vector>
#include <set>
#include <boost/range.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptor/map.hpp>

using namespace std;
using namespace RMN;
using namespace RMN::filemanagers;

// main
int main()
{
	try
	{
		gog_library_latest gll;
		int i = gll.Execute();
		return i;
	}
	catch (exception ex)
	{
		return 0;
	}
}

int gog_library_latest::Execute()
{
	vector<string> allDirectories = filemanagerFunctions::GetAllDirectories();

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
		vector<string> currentlyDownloadedInstallers = filemanagerFunctions::GetInstallerFilesFromDirectory(currentDirectory);

		// get list of files from lgog;
		map<string, string> installerFileNamesFromGOG = filemanagerFunctions::GetGameInstallerFilesFromGOG(currentGame);

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
		if (!filesToGetFromGOG.size())
		{
			continue;
		}
		string downloadFileCommand = "";
		if (filemanagerFunctions::NeedToDownloadAllFiles(filesToGetFromGOG, installerFileNamesFromGOG))
		{
			// TODO: set downloadFileCommand to download all files for that game
		}
		else
		{
			// create comma-separated string of {gamename/fileid}s and pass it to the `--download-file` parameter in lgog
			ostringstream oss;
			copy(begin(filesToGetFromGOG), end(filesToGetFromGOG), ostream_iterator<string>(oss, ","));
			string fileDownloadArguments = oss.str();

			// TODO: set downloadFileCommand to the --download-file version
		}

		// TODO: PERFORM LGOG FILE DOWNLOAD
		// downloadFileCommand = lgogdownloaderCommand + space + down;

		// remove all old installer files that aren't on THE LIST
		filemanagerFunctions::TrimFilesToGogList(currentlyDownloadedInstallers, installerFileNamesFromGOG);

		// for_each(installerFileNamesFromGOG.begin(), installerFileNamesFromGOG.end(), logthis);

		return 1;
	}
}