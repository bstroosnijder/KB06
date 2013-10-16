#include "Game/Marker.h"

namespace Game
{
	Marker::Marker(irr::scene::ISceneManager* p_sceneManager, PlaygroundListener* p_listener,irr::core::vector3df p_position)
		:
		Entity(p_sceneManager, p_listener)
	{
		/*irr::scene::IAnimatedMesh * animMesh = p_sceneManager->getMesh("resources/models/Trafficsign.3ds");
		m_meshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(animMesh,m_meshSceneNode);
		SetMaterialFlags(m_meshSceneNode);*/
		m_meshSceneNode = p_sceneManager->addCubeSceneNode();
		m_meshSceneNode->setPosition(p_position);
		m_max = (p_position.Y + 3);
		m_min = (p_position.Y - 3);
		bool m_up = true;
	}

	int Marker::GetMax()
	{
		return m_max;
	}

	int Marker::GetMin()
	{
		return m_min;
	}

	void Marker::UpdatePosition(float p_deltaTime)
	{
		irr::core::vector3df position = this->GetPosition();
		if (m_up)
		{
			position.Y +=0.20 * p_deltaTime* 60;				
			if (position.Y >= m_max)
			{
				m_up = false;
			}
		} else if (!m_up)
		{
			position.Y -=0.20 * p_deltaTime * 60;				
			if (position.Y <= m_min)
			{
				m_up = true;
			}

		}
		this->SetPosition(position);
	}
}
	