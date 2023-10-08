#pragma once
#include <algorithm>
#include <sstream>
#include <set>
#include <pstream.h>
#include <boost/range.hpp>
#include <iostream>
#include <string>
#include <array>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <vector>
#include <iterator>
#include <map>

using namespace std;

namespace RMN
{
    class gog_library_latest
    {
    public:
        static int Execute();
        void TrimFilesToGogList(vector<string> currentlyDownloadedInstallers, map<string, string> installerFileNamesFromGOG);
        vector<string> GetAllDirectories();
        string GetThisGameCommand(string currentGame);
        string GetAllDirectoriesCommand();
        vector<string> GetInstallerFilesFromDirectory(string currentDirectory);
        string GetInstallerFilesFromDirectoryCommand(string currentDirectory);
        map<string, string> parseInstallerFilesFromLgogReturn(vector<string> thisGameDetailList);
        map<string, string> GetGameInstallerFilesFromGOG(string currentGame);
        template <typename T>
        bool NeedToDownloadAllFiles(vector<T> vv, map<T, T> mm);
        vector<string> splitCLIresults(const char *cmd, string delimiter);
    };

    namespace utility
    {
        class utilityFunctions
        {
        public:
            static string execCLI(const char *cmd);
            static vector<string> split(string s, string delimiter);
            template <typename T>
            static set<T> vectorToSet(const vector<T> &inputVector);
            template <typename T>
            static bool compareVectors(std::vector<T> &v1, std::vector<T> &v2);
        };
    }

    namespace constants
    {
         const string foo;
         const string lsCommand;
         const string rmCommand;
         const string pipeGrepComand;
         const string gameInstallersRoot;
         const string gogDir;
         const string space;
         const string newlineDelimiter;
         const string lgogdownloaderCommand;
         const string lgogdownloaderDownloadDirectoryArguments;
         const string lgogdownloaderDownloadAllFilesArguments;
         const string lgogdownloaderDownladFileArguments;
         const string lgogdownloaderGameArgument;
         const string lgogdownloaderListDetailsArgument;
         const string pathRowConstant;
         const string fileIdRowonstant;
    };

    namespace filemanagers
    {
        class filemanagerFunctions
        {
        public:
            static void TrimFilesToGogList(vector<string> currentlyDownloadedInstallers, map<string, string> installerFileNamesFromGOG);
            static map<string, string> parseInstallerFilesFromLgogReturn(vector<string> thisGameDetailList);
            static map<string, string> GetGameInstallerFilesFromGOG(string currentGame);
            static vector<string> GetAllDirectories();
            static vector<string> GetInstallerFilesFromDirectory(string currentDirectory);
            template <typename T>
            static bool NeedToDownloadAllFiles(vector<T> vv, map<T, T> mm);
        };
    }

    namespace commands{
        class commandAssembler{
            public:
            string GetThisGameCommand(string currentGame);
            string GetAllDirectoriesCommand();
        };
    }
}