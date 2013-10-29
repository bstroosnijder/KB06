#include "Game/ScoreManager.h"

namespace Game
{
	ScoreManager::ScoreManager()
	{
		m_playerPointsDefault[0] = 100;
		m_playerPointsDefault[1] = 100;

		m_playerPoints[0] = m_playerPointsDefault[0];
		m_playerPoints[1] = m_playerPointsDefault[1];

		m_pencilsDefault = 8;
		m_pencilsOwned = m_pencilsDefault;

		m_pointsCastleReached = 10;
		m_pointsPencilBought = -50;
		m_pointsCreatureKilled = 10;
		m_pointsTowerCreated = -100;
		m_pointsTowerDestroyed = 50;
		m_pointsTowerIncreasedSpeed = -200;
		m_pointsTowerIncreasedRange = -100;
		m_pointsTowerIncreasedDamage = -200;
	}

	int ScoreManager::GetPlayerScore(int p_playerNumber)
	{
		return m_playerPoints[p_playerNumber];
	}

	int ScoreManager::GetPencilsOwned()
	{
		return m_pencilsOwned;
	}

	int ScoreManager::GetPencilsDefault()
	{
		return m_pencilsDefault;
	}

	void ScoreManager::ResetPencilsOwned()
	{
		m_pencilsOwned = m_pencilsDefault;
	}

	void ScoreManager::SetPencilsOwned(int p_pencilsOwned)
	{
		m_pencilsOwned = p_pencilsOwned;
	}

	bool ScoreManager::CanBuyPencil(int p_playerNumber)
	{
		return (m_playerPoints[p_playerNumber] + m_pointsPencilBought >= 0);
	}

	bool ScoreManager::CanCreateTower(int p_playerNumber)
	{
		return (m_playerPoints[p_playerNumber] + m_pointsTowerCreated >= 0);
	}

	bool ScoreManager::CanUpgradeTowerSpeed(int p_playerNumber)
	{
		return (m_playerPoints[p_playerNumber] + m_pointsTowerIncreasedSpeed >= 0);
	}

	bool ScoreManager::CanUpgradeTowerRange(int p_playerNumber)
	{
		return (m_playerPoints[p_playerNumber] + m_pointsTowerIncreasedRange >= 0);
	}

	bool ScoreManager::CanUpgradeTowerDamage(int p_playerNumber)
	{
		return (m_playerPoints[p_playerNumber] + m_pointsTowerIncreasedDamage >= 0);
	}

	void ScoreManager::SetPlayerScore(int p_playerNumber, int p_score)
	{
		m_playerPoints[p_playerNumber] = p_score;
	}

	void ScoreManager::ResetPlayerScore(int p_playerNumber)
	{
		m_playerPoints[p_playerNumber] = m_playerPointsDefault[p_playerNumber];
	}

	void ScoreManager::CastleReached(int p_playerNumber)
	{
		m_playerPoints[p_playerNumber] += m_pointsCastleReached;
	}

	void ScoreManager::PencilBought(int p_playerNumber)
	{
		m_playerPoints[p_playerNumber] += m_pointsPencilBought;
		m_pencilsOwned += 1;
	}

	void ScoreManager::CreatureKilled(int p_playerNumber)
	{
		m_playerPoints[p_playerNumber] += m_pointsCreatureKilled;
	}

	void ScoreManager::TowerCreated(int p_playerNumber)
	{
		m_playerPoints[p_playerNumber] += m_pointsTowerCreated;
	}

	void ScoreManager::TowerDestroyed(int p_playerNumber)
	{
		m_playerPoints[p_playerNumber] += m_pointsTowerDestroyed;
	}

	void ScoreManager::TowerIncreasedSpeed(int p_playerNumber)
	{
		m_playerPoints[p_playerNumber] += m_pointsTowerIncreasedSpeed;
	}

	void ScoreManager::TowerIncreasedRange(int p_playerNumber)
	{
		m_playerPoints[p_playerNumber] += m_pointsTowerIncreasedRange;
	}

	void ScoreManager::TowerIncreasedDamage(int p_playerNumber)
	{
		m_playerPoints[p_playerNumber] += m_pointsTowerIncreasedDamage;
	}
}