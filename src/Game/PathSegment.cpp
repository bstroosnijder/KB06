#include "Game/PathSegment.h"

using namespace Game;

PathSegment::PathSegment()
{
	m_point1 = NULL;
	m_point2 = NULL;
}

PathSegment::PathSegment(PathPoint* p_point1, PathPoint* p_point2)
{
	m_point1 = p_point1;
	m_point2 = p_point2;
}

float PathSegment::GetSpeedScale(float p_unitLength)
{
	if (m_point1 == NULL || m_point2 == NULL)
		return 0.0f;

	irr::core::vector3df dif = m_point1->m_point - m_point2->m_point;

	float distance = m_point1->m_point.getDistanceFrom(m_point2->m_point);
	return p_unitLength / distance;

	float xDif = m_point1->m_point.X - m_point2->m_point.X;
	float yDif = m_point1->m_point.Y - m_point2->m_point.Y;
	float zDif = m_point1->m_point.Z - m_point2->m_point.Z;
		
	float distanceBetweenPoints = sqrt(xDif*xDif + yDif*yDif + zDif*zDif);
	
	return p_unitLength / distanceBetweenPoints;
}