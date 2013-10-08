#include "Game/Wave.h"

namespace Game
{
	Wave::Wave(irr::scene::ISceneManager* p_sceneManager)
	{
		m_creaturesSpawned = false;
		m_isActive = true;
		m_sceneManager = p_sceneManager;
		m_timer = new timer();
		m_waveSize = 10;
	}

	Wave::~Wave()
	{

	}

	void Wave::SpawnWave(irr::core::vector3df p_startPosition)
	{
		
		m_isActive = true;
		m_startPosition = p_startPosition;
		m_timer->start();
	}

	void Wave::SpawnCreature(std::vector<Creature*>* p_creatures,PathRoute* p_path)
	{		
		if (m_timer->isRunning())
		{
			if (m_waveSize != 0)
			{
			
				if (m_timer->getTime() == 1)
				{
					p_creatures->push_back(new Creature(m_sceneManager,m_startPosition,p_path));
					m_timer->reset();
					m_creaturesSpawned = true;
					std::cout << "Creature Spawned";
					--m_waveSize;
				}
			}
			else
			{
				m_timer->stop();
			}
		}		
	}

	bool Wave::CheckWaveStatus(std::vector<Creature*>* p_creatures)
	{
		if (m_creaturesSpawned == true && p_creatures->size() == 0)
		{
			m_isActive = false;
		}
		return m_isActive;
	}
}