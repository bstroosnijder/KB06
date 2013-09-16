#include "Utility/Logger.h"
#include "Game/Kernel.h"

int main(int argc, char* argv[])
{
	Utility::Logger* logger = Utility::Logger::GetInstance();
	//Standaard staat file logging op FALSE
	logger->SetFileLoggingState(true);
	logger->SetConsoleLoggingState(false);
	logger->Log(Utility::Logger::LOG_MESSAGE, "Program Started");

	Game::Kernel* kernel = new Game::Kernel();
	kernel->Start();

	delete kernel;

	logger->Log(Utility::Logger::LOG_MESSAGE, "Program Stopped!", __LINE__, __FILE__);
	logger->ResetInstance();
	logger = NULL;

	return 0;
}