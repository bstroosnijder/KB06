#ifndef __GAME__SCOREMANAGER__H__
#define __GAME__SCOREMANAGER__H__

namespace Game
{
	class ScoreManager
	{
	public:
		ScoreManager();

		int GetPlayerScore(int p_playerNumber);
		void SetPlayerScore(int p_playerNumber, int p_score);
		void ResetPlayerScore(int p_playerNumber);

		void CastleReached(int p_playerNumber);
		void PencilBought(int p_playerNumber);
		void CreatureKilled(int p_playerNumber);
		void TowerIncreasedSpeed(int p_playerNumber);
		void TowerIncreasedRange(int p_playerNumber);
		void TowerIncreasedDamage(int p_playerNumber);

	private:
		int m_playerPoints[2];
		int m_playerPointsDefault[2];

		int m_pointsCastleReached;
		int m_pointsPencilBought;
		int m_pointsCreatureKilled;
		int m_pointsTowerIncreasedSpeed;
		int m_pointsTowerIncreasedRange;
		int m_pointsTowerIncreasedDamage;
	};
}

#endif