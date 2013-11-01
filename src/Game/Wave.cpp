#include "Game/Wave.h"

namespace Game
{
	Wave::Wave(irr::scene::ISceneManager* p_sceneManager, PlaygroundListener* p_playgroundListener, int p_waveSize)
	{
		m_playgroundListener = p_playgroundListener;
		m_sceneManager = p_sceneManager;
		m_waveSize = p_waveSize;

		m_creaturesSpawned = 0;
		m_timer = new Timer();
	}

	Wave::~Wave()
	{
		delete m_timer;
		m_timer = NULL;
	}

	void Wave::StartSpawning(irr::core::vector3df p_startPosition)
	{
		m_startPosition = p_startPosition;

		m_creaturesSpawned = 0;
		m_timer->Start();
	}

	void Wave::ResetAndStopSpawning()
	{
		m_creaturesSpawned = 0;
		m_timer->Reset();
	}

	bool Wave::SpawnCreature(PathRoute* p_path)
	{
		Utility::Logger* logger = Utility::Logger::GetInstance();

		if (m_timer->IsRunning() && m_creaturesSpawned < m_waveSize)
		{
			if (m_timer->GetTime() == 1)
			{
				Creature* creature = new Creature(m_sceneManager, m_playgroundListener, m_startPosition, p_path);
				m_playgroundListener->OnCreatureCreated(creature);

				m_timer->Reset();
				--m_creaturesSpawned;

				logger->Log(Utility::Logger::LOG_MESSAGE, "Creature spawned", __LINE__, __FILE__);

				return true;
			}
		}
		else
		{
			m_timer->Stop();
				
			logger->Log(Utility::Logger::LOG_MESSAGE, "Creature spawning stopped", __LINE__, __FILE__);
		}

		return false;
	}

	bool Wave::IsActive()
	{
		return (m_timer->IsRunning());
	}

	bool Wave::AreAllCreaturesSpawned()
	{
		return (m_creaturesSpawned >= m_waveSize);
	}

	int Wave::GetCreaturesSpawned()
	{
		return m_creaturesSpawned;
	}

	void Wave::SetWaveSize(int p_waveSize)
	{
		m_waveSize = p_waveSize;
	}

	int Wave::GetWaveSize()
	{
		return m_waveSize;
	}
}