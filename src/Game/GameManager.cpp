#include "Game/GameManager.h"

using namespace Game;

GameManager::GameManager(irr::IrrlichtDevice* p_device)
{
	m_device = p_device;

	if (m_device != NULL)
	{
		irr::scene::ISceneManager* sceneManager = p_device->getSceneManager();
		irr::ITimer* timer = p_device->getTimer();

		m_playground = new Playground(sceneManager);
		m_deltaTimer = new DeltaTimer(timer);
	}
}

GameManager::~GameManager()
{
	delete m_playground;
	delete m_deltaTimer;

	m_playground = NULL;
	m_deltaTimer = NULL;
}

void GameManager::Update()
{
	m_playground->Update(m_deltaTimer->GetDelta());
}

void GameManager::Render()
{
	m_playground->Render();
}