#include "header.hpp"
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
#include <utility>

using namespace std;
using namespace RMN::utility;
using namespace RMN::constants;

namespace RMN
{
    namespace filemanagers
    {
        class filemanagerFunctions
        {
        public:
            void TrimFilesToGogList(vector<string> currentlyDownloadedInstallers, map<string, string> installerFileNamesFromGOG)
            {
                for (string existingFile : currentlyDownloadedInstallers)
                {
                    // check each `existingFile` to ensure it's on the GOG list.
                    if (installerFileNamesFromGOG.find(existingFile) == installerFileNamesFromGOG.end())
                    {
                        //  If not, delete
                        const char *rmStr = (rmCommand + space + existingFile).c_str();
                        utilityFunctions::execCLI(rmStr);
                    }

                    //  If so, continue
                }
            }
            map<string, string> parseInstallerFilesFromLgogReturn(vector<string> thisGameDetailList)
            {
                // create return dictionary
                map<string, string> gogInstallers;
                bool isInInstallersSection = false;
                string fileId, path;

                // iterate over each line in the sh return
                for (size_t t = 0; t < thisGameDetailList.size(); t++)
                {
                    // capture current line
                    string curLine = thisGameDetailList[t];
                    // is this line where the installer files section begins?
                    if (curLine.rfind("installers", 0) == 0)
                    {
                        // we have found the header for the installers section.
                        //  This line won't have relevant data
                        isInInstallersSection = true;
                        continue;
                    }
                    else if (!isInInstallersSection)
                    {
                        continue;
                    }
                    if (isInInstallersSection)
                    {
                        // this identifies the filename so we can compare against the library
                        if (curLine.rfind(pathRowConstant, 0) == 0)
                        {
                            string filename = curLine.substr(curLine.find_last_of("/") + 1);
                            path = filename;
                        }
                        // this identifies the file id so we can request it from lgogdownloader
                        if (curLine.rfind(fileIdRowConstant, 0) == 0)
                        {
                            string filename = curLine.substr(curLine.find_last_of(":") + 1);
                            fileId = filename;
                        }
                    }
                    // if this line starts with a tab, move to the next iterand
                    if (curLine.rfind("\t") == 0)
                    {
                        continue;
                    }
                    else
                    {
                        // we're done with this particular file, record it and move on
                        if (!fileId.empty() && !path.empty())
                        {
                            gogInstallers[fileId] = path;
                        }

                        break;
                    }
                }

                return gogInstallers;
            }
            map<string, string> GetGameInstallerFilesFromGOG(string currentGame)
            {
                string thisGameCommand = GetThisGameCommand(currentGame);
                map<string, string> installerFileNamesFromGOG = parseInstallerFilesFromLgogReturn(splitCLIresults(thisGameCommand.c_str(), newlineDelimiter));
                return installerFileNamesFromGOG;
            }

            vector<string> GetAllDirectories()
            {
                // get all directories in installer root
                string dircmd = GetAllDirectoriesCommand();
                const char *boop = dircmd.c_str();
                string allDirectoriesStr = RMN::utility::execCLI(boop);

                // get all directories from console return
                return split(allDirectoriesStr, newlineDelimiter);
            }

            vector<string> GetInstallerFilesFromDirectory(string currentDirectory)
            {
                string dircmd = GetInstallerFilesFromDirectoryCommand(currentDirectory);
                const char *boop = dircmd.c_str();
                return split(execCLI(boop), newlineDelimiter);
            }

            template <typename T>
            bool NeedToDownloadAllFiles(vector<T> vv, map<T, T> mm)
            {
                vector<T> mapVector;
                boost::copy(mm | boost::adaptors::map_keys, std::back_inserter(mapVector));
                return compareVectors(vv, mapVector);
            }
        };
    }
}