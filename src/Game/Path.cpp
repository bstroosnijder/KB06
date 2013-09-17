#include "Game/Path.h"

#include "Game/PathSegment.h"

using namespace Game;

Path::Path()
{
	m_pathSegmentStart = NULL;
	m_pathSegmentEnd = NULL;
}

Path::~Path()
{
	m_pathSegments.clear();
}