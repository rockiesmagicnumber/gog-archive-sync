#include <pstream.h>
#include <iostream>
#include <string>
#include <array>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <vector>

const std::string lsCommand("ls -p");
const std::string pipeGrepComand("| grep -v /");
const std::string gameInstallersRoot("/media/the-archive/Game-Installers/");
const std::string gogDir("gog/");
const std::string space(" ");
const std::string newlineDelimiter("\n");

// execute CLI function and return the output from stdout as a string - https://stackoverflow.com/a/478960
std::string execCLI(const char *cmd)
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