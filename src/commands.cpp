#include <headers.hpp>

namespace RMN
{
    namespace commands
    {
        class commandAssembler
        {
        public:
            string GetThisGameCommand(string currentGame)
            {
                return lgogdownloaderCommand + space + lgogdownloaderListDetailsArgument + space + lgogdownloaderGameArgument + space + currentGame;
            }

            string GetAllDirectoriesCommand()
            {
                return lsCommand + space + gameInstallersRoot;
            }

            string GetInstallerFilesFromDirectoryCommand(string currentDirectory)
            {
                return lsCommand + space + gameInstallersRoot + currentDirectory + gogDir + space + pipeGrepComand;
            }
        }
    }
}