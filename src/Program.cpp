#include "Game/kernel.h"


int main (int argc, char* argv[])
{
	Camera::Calibration calibration = Camera::Calibration();
	calibration.Start();
	return 0;
}


