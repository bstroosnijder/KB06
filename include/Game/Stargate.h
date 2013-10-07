#ifndef __GAME__STARGATE__H__
#define __GAME__STARGATE__H__

#include "Entity.h"

namespace Game
{
	class Stargate : public Entity
	{
		Stargate(irr::scene::ISceneManager*, irr::core::vector3df&);
	};
}

#endif