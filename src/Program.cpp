#include "Utility/Logger.h"
#include "Game/kernel.h"

int main (int argc, char* argv[])
{
	Utility::Logger* logger = Utility::Logger::GetInstance();
	logger->SetFileLoggingState(false);
	logger->Log(Utility::Logger::LOG_MESSAGE, "Main: Game started");

	if (true)
	{
		Game::Kernel* kernel = new Game::Kernel();
		if (argc > 1)
		{
			kernel->SetMultiThreaded(false);
		}
		else
		{
			kernel->SetMultiThreaded(true);
		}
		kernel->Start();
		delete kernel;
	}
	else
	{
		Camera::Calibration* calibration = new Camera::Calibration();
		calibration->Start();
		delete calibration;
	}

	logger->Log(Utility::Logger::LOG_MESSAGE, "Main: Game stopped");
	Utility::Logger::ResetInstance();

	return 0;
}