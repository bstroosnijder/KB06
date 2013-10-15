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
		
		
		/**
		* @brief Returns the max y position that the marker may go
		*/
		int GetMax();
		/**
		* @brief returns the min y position that the marker may go
		*/
		int GetMin();

		void UpdatePosition(float p_deltaTimer);
	private:	
		int m_max;
		int m_min;
		bool m_up;
	};
}
#endif