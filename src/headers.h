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

using namespace std;

namespace constants
{
    const string lsCommand("ls -p");
    const string pipeGrepComand("| grep -v /");
    const string gameInstallersRoot("/media/the-archive/Game-Installers/");
    const string gogDir("gog/");
    const string space(" ");
    const string newlineDelimiter("\n");

    namespace lgogdownloader
    {
        const string lgogdownladerCommand("lgogdownloader --platform w+l");
        const string lgogdownloaderDownloadArguments("--download --directory /media/the-archive/Game-Installers/ --subdir-installers gog");
        const string lgogdownloaderGameArgument("--game");
        const string lgogdownloaderListDetailsArgument("--list-details");
        const string pathRowConstant("\tpath:");
        const string fileIdRowConstant("\tid:");
    }
}

namespace goglibrarylatest
{
    using namespace constants;
    using namespace constants::lgogdownloader;
    // execute CLI function and return the output from stdout as a string - https://stackoverflow.com/a/478960
    string execCLI(const char *cmd)
    {
        array<char, 128> buffer;
        string result;
        unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        if (!pipe)
        {
            throw runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
        {
            result += buffer.data();
        }
        return result;
    }

    // for string delimiter - taken directly from https://stackoverflow.com/a/46931770
    vector<string> split(string s, string delimiter)
    {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        string token;
        vector<string> res;

        while ((pos_end = s.find(delimiter, pos_start)) != string::npos)
        {
            token = s.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back(token);
        }

        res.push_back(s.substr(pos_start));
        return res;
    }

    // convert a vector to a set
    template <typename T>
    set<T> vectorToSet(const vector<T> &inputVector)
    {
        set<string> s(inputVector.begin(), inputVector.end());
        return s;
    }

    vector<string> splitCLIresults(const char *cmd, string delimiter)
    {
        return split(execCLI(cmd), delimiter);
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

    void logthis(string s)
    {
        cout << s << endl;
    }
}