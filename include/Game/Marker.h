#ifndef __GAME__MARKER__H__
#define __GAME__MARKER__H__

#include "Game/Entity.h"

namespace Game
{
	/**
	 * @brief	Used as a marker to display the position PathPoint in a Path.
	 *			
	 * @author	Michel van Os
	 */
	class Marker : public Entity
	{		
	public:
		/**
		 * @brief	Create a Marker as the specified position.
		 *
		 * @param	p_sceneManager is used to attach the Marker SceneNode to the manager.
		 * @param	p_playgroundListener is used to send events from the Marker to the Playground.
		 * @param	p_position The marker will be positioned on p_position.
		 */
		Marker(irr::scene::ISceneManager* p_sceneManager, PlaygroundListener* p_playgroundListener, irr::core::vector3df p_position);
		
		/**
		 * @brief	Updates the position and rotation of the Marker.
		 *
		 *			Makes the Marker jump and spin around.
		 * @author	Michel van Os.
		 * @param	p_deltaTimer The delta time is used for a constant speed.
		 */
		void UpdatePosition(float p_deltaTimer);

	private:
		float m_jump;
		irr::core::vector3df m_positionStart;
	};
}
#endif