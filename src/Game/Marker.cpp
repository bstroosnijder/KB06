#include "Game/Marker.h"

namespace Game
{
	Marker::Marker(irr::scene::ISceneManager* p_sceneManager, PlaygroundListener* p_listener,irr::core::vector3df p_position)
		:
		Entity(p_sceneManager, p_listener)
	{
		m_animatedMesh = p_sceneManager->getMesh("resources/models/marker/Sims_CrystalV01.X");
		
		m_meshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh, m_meshSceneNode);
		m_meshSceneNode->setPosition(p_position);
		m_meshSceneNode->setScale(irr::core::vector3df(0.2f));

		m_jump = 0.0f;
		m_positionStart = GetPosition();

		SetMaterialFlags(m_meshSceneNode);
	}

	void Marker::UpdatePosition(float p_deltaTime)
	{
		irr::core::vector3df translation = m_positionStart;
		irr::core::vector3df rotation = m_meshSceneNode->getRotation();

		//Jump
		m_jump += p_deltaTime * 60 * 0.1f;
		translation.Y = translation.Y + sin(m_jump) * 10 + 5;
		
		//Rotate
		rotation.Y += p_deltaTime * 60 * 2.0f;

		m_meshSceneNode->setPosition(translation);
		m_meshSceneNode->setRotation(rotation);
	}
}
	