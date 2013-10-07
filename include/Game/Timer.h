#ifndef __GAME__TIMER__H__
#define __GAME__TIMER__H__

#include <iostream>
#include <conio.h>
#include <time.h>	// class needs this inclusion

namespace Game
{
	class timer {
	public:
		timer();
		void           start();
		void           stop();
		void           reset();
		bool           isRunning();
		unsigned long  getTime();
		bool           isOver(unsigned long seconds);
	private:
		bool           resetted;
		bool           running;
		unsigned long  beg;
		unsigned long  end;
	};
}

#endif