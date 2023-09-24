#include <pstream.h>
#include <iostream>
#include <string>
#include <array>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <vector>

using namespace std;

// prototypes
string execCLI(const char *cmd);
std::vector<std::string> split(std::string s, std::string delimiter);

// main
int main()
{
	const string lsCommand("ls -p");
	const string pipeGrepComand("| grep -v /");
	const string gameInstallersRoot("/media/the-archive/Game-Installers/");
	const string gogDir("gog/");
	const string space(" ");
	const string newlineDelimiter("\n");

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

// execute CLI function and return the output from stdout as a string - https://stackoverflow.com/a/478960
string execCLI(const char *cmd)
{
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
	if (!pipe)
	{
		throw std::runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
	{
		result += buffer.data();
	}
	return result;
}

// for string delimiter - taken directly from https://stackoverflow.com/a/46931770
std::vector<std::string> split(std::string s, std::string delimiter)
{
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
	{
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}