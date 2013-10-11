#ifndef __GAME_PATHFOLLOWER__H__
#define __GAME_PATHFOLLOWER__H__

#include "Entity.h"
#include "PathRoute.h"

namespace Game
{
	class PathFollower : public Entity
	{
	public:
		PathFollower(PathRoute* p_pathRoute);
		void FollowPath(float p_deltaTime);

		void StartFollowing();
		void StopFollowing();
		void ResumeFollowing();
		bool IsFollowing();

		void SetSpeed(float p_speed);
		float GetSpeed();
		PathPoint* m_pointCurrent;

	private:
		bool m_following;

		PathRoute* m_pathRoute;
		PathRoute::iterator m_pointCurrentIt;
		PathRoute::iterator m_pointNextIt;
		
		PathPoint* m_pointNext;

		irr::core::vector3df m_segmentLength;
		irr::core::vector3df m_segmentPosition;

		float m_speedScale;
		float m_unitLength;
		float m_speed;

		void FollowNextSegment();
		void FollowCurrentSegment(float p_deltaTime);
		bool IsEndOfSegmentReached();
	};
};

#endif