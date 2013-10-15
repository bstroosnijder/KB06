#ifndef __GAME__CREATURE__H__
#define __GAME__CREATURE__H__

#include "PathFollower.h"
#include "PathRoute.h"

namespace Game
{
	/**
	* @brief	Creature class.
	* @author	Thomas Gravekamp
	*/
	class Creature : public PathFollower
	{
	public:
		/**
		 * @brief Initialize Creature with the overloaded constructor
		 * @param p_sceneManager is used to attach the Creature scenenode to the manager
		 * @param Playground listener is used to send events from creature to playground
		 * @param The creature will be positioned on p_position
		 * @param The creature needs p_pathRoute to know which path to follow
		 * @param p_selector is to add collisiondetection with the Terrain
		 */
		Creature(irr::scene::ISceneManager* p_sceneManager,
			PlaygroundListener*,
			irr::core::vector3df p_position,
			PathRoute* p_pathRoute,
			irr::scene::ITriangleSelector* p_selector);

		/**
		 * @brief	Destroys the Creature
		 */
		~Creature();

		/**
		 * @brief	Moves the Creature along the Path.
		 *
		 *			The speed of the Creature is adapter to the delta time.
		 * @param	p_deltaTime	The delta time used for the movement.
		 * @author	Michel van Os.
		 */
		void FollowPath(float p_deltaTime);

		/**
		 * @brief	Set the HealthPoints of the creature
		 * @param	The HP value is p_healthPoints
		 */
		void SetHealthPoints(int p_healthPoints);

		/**
		 * @brief	Return the HealthPoints of the creature
		 */
		int GetHealthPoints();

	private:
        int m_healthPoints;
		irr::scene::ISceneNodeAnimator* m_sceneNodeAnimator;
	};
}

#endif