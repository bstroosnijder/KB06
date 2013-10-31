#include "Game/Path.h"

namespace Game
{
	Path::Path()
	{
		m_pathPoints = NULL;
		m_pointBegin = NULL;
		m_pointEnd = NULL;
	}

	Path::~Path()
	{
		m_pathPoints->remove(m_pointBegin);
		m_pathPoints->remove(m_pointEnd);
		m_pointBegin = NULL;
		m_pointEnd = NULL;

		m_pathPoints->clear();
		delete m_pathPoints;
		m_pathPoints = NULL;
	}
}