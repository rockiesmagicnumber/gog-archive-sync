#include <string>

using namespace std;
namespace RMN
{
    namespace constants
    {
        static const string foo = "";
        static const string lsCommand = "ls -p";
        static const string rmCommand = "rm -r";
        static const string pipeGrepComand = "| grep -v /";
        static const string gameInstallersRoot = "/media/the-archive/Game-Installers/";
        static const string gogDir = "gog/";
        static const string space = " ";
        static const string newlineDelimiter = "\n";
        static const string lgogdownloaderCommand = "lgogdownloader --platform w+l";
        static const string lgogdownloaderDownloadDirectoryArguments = "--directory /media/the-archive/Game-Installers/ --subdir-installers gog";
        static const string lgogdownloaderDownloadAllFilesArguments = "--download ";
        static const string lgogdownloaderDownladFileArguments = "--download-file";
        static const string lgogdownloaderGameArgument = "--game";
        static const string lgogdownloaderListDetailsArgument = "--list-details";
        static const string pathRowConstant = "\tpath:";
        static const string fileIdRowConstant = "\tid:";
    }
}