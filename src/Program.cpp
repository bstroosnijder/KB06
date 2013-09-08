#include "Game/Kernel.h"

int main(int argc, char* argv[])
{
	Game::Kernel* kernel = new Game::Kernel();
	kernel->Start();

	delete kernel;
	return 0;
}