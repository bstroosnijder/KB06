#include "Game/Path.h"

#include "Game/PathSegment.h"

using namespace Game;

Path::Path()
{
	m_pointBegin = NULL;
	m_pointEnd = NULL;
}

Path::~Path()
{
	m_pathPoints->clear();
	delete m_pathPoints;
}