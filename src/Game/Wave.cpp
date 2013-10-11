#include "Game/Wave.h"

namespace Game
{
	Wave::Wave(irr::scene::ISceneManager* p_sceneManager)
	{
		m_sceneManager = p_sceneManager;

		m_creaturesSpawned = false;
		m_isActive = true;
		m_timer = new Timer();
		m_waveSize = 100;
	}

	Wave::~Wave()
	{
		delete m_timer;

		m_timer = NULL;
	}

	void Wave::SpawnWave(irr::core::vector3df p_startPosition)
	{
		m_isActive = true;

		m_startPosition = p_startPosition;
		m_timer->Start();
	}

	void Wave::SpawnCreature(std::list<Creature*>& p_creatures, PathRoute* p_path,irr::scene::ITriangleSelector* p_selector)
	{		
		if (m_timer->IsRunning())
		{
			if (m_waveSize != 0)
			{
				if (m_timer->GetTime() == 1)
				{
					p_creatures.push_back(new Creature(m_sceneManager,m_startPosition,p_path,p_selector));

					m_timer->Reset();
					m_creaturesSpawned = true;
					std::cout << "Creature Spawned";
					--m_waveSize;
				}
			}
			else
			{
				m_timer->Stop();
			}
		}		
	}

	bool Wave::CheckWaveStatus(std::list<Creature*>& p_creatures)
	{
		if (m_creaturesSpawned == true && p_creatures.size() == 0)
		{
			m_isActive = false;
		}

		return m_isActive;
	}
}