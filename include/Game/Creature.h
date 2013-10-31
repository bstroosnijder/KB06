#ifndef __GAME__CREATURE__H__
#define __GAME__CREATURE__H__

#include "PathFollower.h"
#include "PathRoute.h"
#include "Terrain.h"

namespace Game
{
	/**
	 * @brief	Creature class.
	 *
	 * @author	Thomas Gravekamp
	 */
	class Creature : public PathFollower
	{
	public:
		/**
		 * @brief Initialize Creature with the overloaded constructor
		 *
		 * @param p_sceneManager		is used to attach the Creature scenenode to the manager
		 * @param p_playgroundListener	is used to send events from creature to playground
		 * @param p_position			The creature will be positioned on p_position
		 * @param p_pathroute			The creature needs p_pathRoute to know which path to follow
		 */
		Creature(irr::scene::ISceneManager* p_sceneManager,
				PlaygroundListener* p_playgroundListener,
				irr::core::vector3df p_position,
				PathRoute* p_pathRoute);

		/**
		 * @brief	Destroys the Creature
		 */
		~Creature();

		/**
		 * @brief	Moves the Creature along the Path.
		 *
		 *			The speed of the Creature is adapter to the delta time
		 * @param	p_deltaTime	The delta time used for the movement
		 * @param	p_terrain	The terrain on which the path is a part of
		 * @param	p_terrain	The terrain.
		 */
		void FollowPath(float p_deltaTime, Terrain* p_terrain);

		/**
		 * @brief	Set the HealthPoints of the Creature.
		 * @param	p_healthPoints The new HealthPoint for the Creature.
		 */
		void DecreaseHealthPoints(double p_healthPoints);

		/**
		 * @brief	Return the HealthPoints of the creature
		 * @return	double Healthpoints.
		 */
		double GetHealthPoints();

		/**
		 * @brief	Returns the boudingbox of this creature.
		 * @return	irr::core::aabbox3d<irr::f32> The bounding box.
		 */
		irr::core::aabbox3d<irr::f32> GetBoundingbox();

	private:
        double m_healthPoints;
	};
}

#endif