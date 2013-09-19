#ifndef __GAME__TOWER__H__
#define __GAME__TOWER__H__

#include "Object.h"

namespace Game
{
	class Tower : public Object
	{
	public:
		Tower(irr::scene::ISceneManager*, irr::core::vector3df);
	};
}

#endif