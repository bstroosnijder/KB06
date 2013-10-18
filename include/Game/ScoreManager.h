#ifndef __GAME__SCOREMANAGER__H__
#define __GAME__SCOREMANAGER__H__

namespace Game
{
	class ScoreManager
	/**
	 * @brief	TODO
	 *			
	 * @author	Alex Hodes
	 */
	{
	public:
		/**
		* @brief	TODO
		*/	
		ScoreManager();

		/**
		* @brief	TODO
		*/	
		int GetPlayerScore(int p_playerNumber);

	   /**
		* @brief	TODO
		*/	
		void SetPlayerScore(int p_playerNumber, int p_score);
		/**
		* @brief	TODO
		*/
		void ResetPlayerScore(int p_playerNumber);

		/**
		* @brief	TODO
		*/
		void CastleReached(int p_playerNumber);

		/**
		* @brief	TODO
		*/
		void PencilBought(int p_playerNumber);

		/**
		* @brief	TODO
		*/
		void CreatureKilled(int p_playerNumber);

		/**
		* @brief	TODO
		*/
		void TowerIncreasedSpeed(int p_playerNumber);

		/**
		* @brief	TODO
		*/
		void TowerIncreasedRange(int p_playerNumber);

		/**
		* @brief	TODO
		*/
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