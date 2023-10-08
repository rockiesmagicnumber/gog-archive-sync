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

namespace RMN
{
    namespace utility
    {
        class utilityFunctions
        {
        public:
            // execute CLI function and return the output from stdout as a string - https://stackoverflow.com/a/478960
            static string execCLI(const char *cmd)
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

            // https://stackoverflow.com/a/10506620
            template <typename T>
            bool compareVectors(std::vector<T> &v1, std::vector<T> &v2)
            {
                std::sort(v1.begin(), v1.end());
                std::sort(v2.begin(), v2.end());
                return v1 == v2;
            }
        };
    }
}