#ifndef __GAME_PATHFOLLOWER__H__
#define __GAME_PATHFOLLOWER__H__

#include "Entity.h"
#include "PathRoute.h"

namespace Game
{
	/**
	 * @brief	The PathFollower folows a PathRoute.
	 *
	 *			The speed of the PathFollower will be adapted by the delta time and
	 *			the size of a path segment to maintain a constant speed.
	 *
	 * @author	Michel van os
	*/
	class PathFollower : public Entity
	{
	public:
		PathFollower(irr::scene::ISceneManager*, PlaygroundListener*, PathRoute* p_pathRoute);

		/**
		 * @brief	Moves the Creature along the Path.
		 *
		 *			The speed of the PathFollower is adapter to the delta time.
		 * @author	Michel van Os.
		 * @param	p_deltaTime	The delta time used for the movement.
		 */
		void FollowPath(float p_deltaTime);

		/**
		 * @brief	The PathFollower starts following the PathRoute.
		 *
		 *			The PathFollower starts following the PathRoute
		 *			and is positioned to the begin of the PathRoute.
		 * @author	Michel van Os.
		 */
		void StartFollowing();

		/**
		 * @brief	The PathFollower stops following the PathRoute.
		 *			
		 * @author	Michel van Os.
		 */
		void StopFollowing();

		/**
		 * @brief	The PathFollower resumes following the PathRoute.
		 *
		 *			Unlike StartFollowing(). ResumeFollowing() does not
		 *			place the PathFollower to the begin of the PathRoute.
		 * @author	Michel van Os.
		 */
		void ResumeFollowing();

		/**
		 * @brief	Returns wheter the PathFollower is following the PathRoute.
		 *			
		 * @author	Michel van Os.
		 */
		bool IsFollowing();

		/**
		 * @brief	Returns wheter the PathFollower reached the end of the PathSegment. 
		 *			
		 * @author	Michel van Os.
		 */
		bool IsEndOfSegmentReached();

		/**
		 * @brief	Returns wheter the PathFollower reached the end of the PathRoute.
		 *			
		 *			If the value returned is true. Then the value returned by
		 *			IsEndOfSegmentReached will also be true.
		 * @author	Michel van Os.
		 */
		bool IsEndOfRouteReached();
		

		/**
		 * @brief	Sets the speed.
		 *			
		 * @author	Michel van Os.
		 * @param	p_speed The new speed.
		 */
		void SetSpeed(float p_speed);

		/**
		 * @brief	Returns the speed.
		 *			
		 * @author	Michel van Os.
		 */
		float GetSpeed();

	private:
		/**
		 * @brief	True if the PathFollower should follow the Pathroute.
		 *
		 * @author	Michel van os.
		 */
		bool m_following;

		/**
		 * @brief	The PathRoute the PathFollower should follow.
		 *
		 * @author	Michel van os.
		 */
		PathRoute* m_pathRoute;

		/**
		 * @brief	The current PathRoute::iterator.
		 *
		 *			The PathFollower moves from m_pointCurrentIt towards m_pointNextIt.
		 * @author	Michel van os.
		 */
		PathRoute::iterator m_pointCurrentIt;

		/**
		 * @brief	The next PathRoute::iterator.
		 *
		 *			The PathFollower moves from m_pointCurrentIt towards m_pointNextIt.
		 * @author	Michel van os.
		 */
		PathRoute::iterator m_pointNextIt;

		/**
		 * @brief	The current PathPoint.
		 *
		 * @author	Michel van os.
		 */
		PathPoint* m_pointCurrent;

		/**
		 * @brief	The next PathPoint.
		 *
		 * @author	Michel van os.
		 */
		PathPoint* m_pointNext;

		/**
		 * @brief	The length of the segment.
		 *
		 * @author	Michel van os.
		 */
		irr::core::vector3df m_segmentLength;

		/**
		 * @brief	The current relative position on the segment.
		 *
		 * @author	Michel van os.
		 */
		irr::core::vector3df m_segmentPosition;
		irr::core::vector3df m_toTarget;

		/**
		 * @brief	The speed scale for the PathFollower adapted to the length of the segment.
		 *
		 * @author	Michel van os.
		 */
		float m_speedScale;

		/**
		 * @brief	The length of one unit.
		 *
		 * @author	Michel van os.
		 */
		float m_unitLength;

		/**
		 * @brief	The speed for the PathFollower
		 *
		 * @author	Michel van os.
		 */
		float m_speed;
		

		/**
		 * @brief	Places the PathFollower to the begin of the next segment.
		 *
		 * @author	Michel van os.
		 */
		void FollowNextSegment();

		/**
		 * @brief	Moves the PathFollower along the current segment.
		 *
		 * @author	Michel van os.
		 * @param	p_deltaTime The deltatime.
		 */
		void FollowCurrentSegment(float p_deltaTime);
	};
};

#endif