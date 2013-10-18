#ifndef __GAME__PLAYGROUNDLISTENER__H__
#define __GAME__PLAYGROUNDLISTENER__H__

namespace Game
{
	class Creature;
	class Projectile;

	/**
	 * @brief	The PlaygroundListener handles the events triggered by Game Entities.
	 * @author	Michel van Os.
	 */
	class PlaygroundListener
	{
	public:
		/**
		* @brief	Triggered when a Projectile is created.
		* @author	Michel van Os.
		* @param	p_projectile The created Projectile.
		*/
		virtual void OnProjectileCreated(Projectile* p_projectile) = 0;

		/**
		 * @brief	Triggered when a Projectile is destroyed.
		 * @author	Michel van Os.
		 * @param	p_projectile The destroyed Projectile.
		 */
		virtual void OnProjectileDestroyed(Projectile* p_projectile) = 0;
		
		/**
		 * @brief	Triggered when a Creature is created.
		 * @author	Michel van Os.
		 * @param	p_creature The created Creature.
		 */
		virtual void OnCreatureCreated(Creature* p_creature) = 0;

		/**
		 * @brief	Triggered when a Creature is destoyed.
		 * @author	Michel van Os.
		 * @param	p_creature The destroyed Creature.
		 */
		virtual void OnCreatureDestroyed(Creature* p_creature) = 0;

		/**
		 * @brief	Triggered when a Creature is hit by a Projectile.
		 * @author	Michel van Os.
		 * @param	p_creature The Create that is hit by the Projectile.
		 * @param	p_projectile The Projectile that hit the Creature.
		 */
		virtual void OnCreatureHit(Creature* p_creature, Projectile* p_projectile) = 0;

		/**
		 * @brief	Triggered when a Creature reached the end of it's PathRoute.
		 * @author	Michel van Os.
		 * @param	p_creature The Creature that reached the end of the PathRoute.
		 */
		virtual void OnCreatureRouteEndReached(Creature* p_creature) = 0;
	};
}

#endif