#ifndef __GAME__MARKER__H__
#define __GAME__MARKER__H__

#include "Game/Entity.h"

namespace Game
{
	class Marker : public Entity
	{		
	public:
		/**
		 * @brief Initialize marker with the overloaded constructor
		 * @param p_sceneManager is used to attach the marker scenenode to the manager
		 * @param Playground listener is used to send events from marker to playground
		 * @param The marker will be positioned on p_position
		 */
		Marker(irr::scene::ISceneManager* p_sceneManager, PlaygroundListener* p_listener,irr::core::vector3df p_position);
		
		void UpdatePosition(float p_deltaTimer);
	private:
		float m_jump;
		irr::core::vector3df m_positionStart;
	};
}
#endif