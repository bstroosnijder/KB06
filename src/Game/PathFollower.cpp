#include "Game/PathFollower.h"

namespace Game
{
	PathFollower::PathFollower(irr::scene::ISceneManager* p_sceneManager,
			PlaygroundListener* p_playgroundListener,
			PathRoute* p_pathRoute)
			:
			Entity(p_sceneManager, p_playgroundListener)
	{
		m_following = false;
		m_pathRoute = p_pathRoute;
		m_pointCurrent = NULL;
		m_pointNext = NULL;

		//Constant values
		m_unitLength = 10.0f;
		m_speed = 0.08f;
	}

	void PathFollower::FollowPath(float p_deltaTime)
	{
		if (m_following)
		{
			if (IsEndOfSegmentReached())
			{
				FollowNextSegment();
			}
			else
			{
				FollowCurrentSegment(p_deltaTime);
			}
		}
	}

	void PathFollower::StartFollowing()
	{
		irr::core::vector3df position;

		m_following = true;

		m_pointCurrentIt = m_pathRoute->begin();
		m_pointNextIt = m_pointCurrentIt;
		std::advance(m_pointNextIt, 1);

		m_pointCurrent = (*m_pointCurrentIt);
		m_pointNext = (*m_pointNextIt);

		m_segmentLength = m_pointNext->m_point - m_pointCurrent->m_point;

		m_speedScale = m_unitLength / m_pointCurrent->m_point.getDistanceFrom(m_pointNext->m_point);
		position = m_pointCurrent->m_point + (m_segmentLength * m_segmentPosition);
		m_meshSceneNode->setPosition(position);

		m_toTarget = m_pointNext->m_point - m_pointCurrent->m_point;
		m_meshSceneNode->setRotation(m_toTarget.getHorizontalAngle());
	}

	void PathFollower::StopFollowing()
	{
		m_following = false;
	}

	void PathFollower::ResumeFollowing()
	{
		m_following = true;
	}

	bool PathFollower::IsFollowing()
	{
		return m_following;
	}

	bool PathFollower::IsEndOfSegmentReached()
	{
		return (m_segmentPosition.X >= 1);
	}

	bool PathFollower::IsEndOfRouteReached()
	{
		return (m_pointNext == m_pathRoute->back() && IsEndOfSegmentReached());
	}

	void PathFollower::SetSpeed(float p_speed)
	{
		m_speed = p_speed;
	}

	float PathFollower::GetSpeed()
	{
		return m_speed;
	}

	void PathFollower::FollowNextSegment()
	{
		irr::core::vector3df position;
		std::list<PathPoint*>::iterator it = m_pointNextIt;
		std::list<PathPoint*>::iterator itEnd = m_pathRoute->end();
		std::advance(it, 1);
		
		//If the end of the route is not reached
		if (it != itEnd)
		{
			//Select the next PathPoints inside the PathRouet
			std::advance(m_pointCurrentIt, 1);
			std::advance(m_pointNextIt, 1);

			m_pointCurrent = (*m_pointCurrentIt);
			m_pointNext = (*m_pointNextIt);

			m_segmentLength = m_pointNext->m_point - m_pointCurrent->m_point;
			m_speedScale = m_unitLength / m_pointCurrent->m_point.getDistanceFrom(m_pointNext->m_point);

			m_segmentPosition -= 1;
			position = m_pointCurrent->m_point + (m_segmentLength * m_segmentPosition);
			m_meshSceneNode->setPosition(position);
		}
	}

	void PathFollower::FollowCurrentSegment(float p_deltaTime)
	{
		irr::core::vector3df position;
		m_segmentPosition += m_speed * m_speedScale * p_deltaTime * 60;
		position = m_pointCurrent->m_point + (m_segmentLength * m_segmentPosition);
		m_meshSceneNode->setPosition(position);

		m_toTarget = m_pointNext->m_point - m_pointCurrent->m_point;
		m_meshSceneNode->setRotation(m_toTarget.getHorizontalAngle());
	}
}