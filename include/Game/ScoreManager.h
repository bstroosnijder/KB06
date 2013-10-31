#ifndef __GAME__SCOREMANAGER__H__
#define __GAME__SCOREMANAGER__H__

namespace Game
{
	/**
	 * @brief	Manages the score for both the defender and the attacker players.
	 *
	 *			The ScoreManager also keeps the amount of pencils bought by the attacker.
	 *			Note that only the GameManager knows the current attacker. So
	 *			when the players changes sides, the amount of pencils bought
	 *			must be resest to the default amount of pencils.
	 *
	 * @author	Michel van Os.
	 */
	class ScoreManager
	{
	public:
		/**
		* @brief	Constructs the scoremanager
		*/	
		ScoreManager();

		/**
		* @brief	Returns the score of player p_playerNumber.
		* @return	Returns the score of player p_playerNumber.
		*
		* @param	p_playerNumber The number of the player of which
		*			the score should be returned.
		* @return	The score of player p_playerNumber.
		*/	
		int GetPlayerScore(int p_playerNumber);

		/**
		 * @brief	Returns the amount of pencils owned by the attacker.
		 * @return	Returns the amount of pencils owned by the attacker.
		 *
		 * @author	Michel van Os.
		 * @return	The amount of pencils owned by the attacker.
		*/	
		int GetPencilsOwned();

		/**
		 * @brief	Returns the default amount of pencils owned by the attacker.
		 * @return	Returns the default amount of pencils owned by the attacker.
		 *
		 *			The defeault amount of pencils are the amount of pencils
		 *			owned by the attacker when a round starts.
		 * @author	Michel van Os.
		 */
		int GetPencilsDefault();

		/**
		 * @brief	Resets the amount of pencils owned to the default amount
		 *			of pencils.
		 *
		 * @author	Michel van Os.
		 */
		void ResetPencilsOwned();

		/**
		 * @brief	Sets the amount of pencils owned by the attacker.
		 *
		 * @author	Michel van Os.
		 * @param	p_pencilsOwned The new amount of pencils.
		 */
		void SetPencilsOwned(int p_pensilsOwned);

		/**
		 * @brief	Returns whether or not the attacker is able to buy a pencil.
		 *
		 * @author	Michel van Os.
		 * @param	p_playerNumber The number of the player to check if his score
					is high enough to buy a pencil.
		 * @return	Whether or not the attacker is able to buy a pencil.
		 */
		bool CanBuyPencil(int p_playerNumber);

		/**
		 * @brief	Returns whether or not the player with player number p_playerNumber
					is able to create a Tower.
		 *
		 * @author	Michel van Os.
		 * @param	p_playerNumber The number of the player to check if his score
					is high enough to create a Tower.
		 * @return	Whether or not the player with p_playerNumber is able to create
					a Tower.
		 */
		bool CanCreateTower(int p_playerNumber);

		/**
		 * @brief	Returns whether or not the player with player number p_playerNumber
					is able to upgrade the speed of a Tower.
		 *
		 * @author	Michel van Os.
		 * @param	p_playerNumber The number of the player to check if his score
					is high enough to upgrade the speed of a Tower.
		 * @return	Whether or not the player with p_playerNumber is able to upgrade
					the speed of a Tower.
		 */
		bool CanUpgradeTowerSpeed(int p_playerNumber);

		/**
		 * @brief	Returns whether or not the player with player number p_playerNumber
					is able to upgrade the range of a Tower.
		 *
		 * @author	Michel van Os.
		 * @param	p_playerNumber The number of the player to check if his score
					is high enough to upgrade the range of a Tower.
		 * @return	Whether or not the player with p_playerNumber is able to upgrade
					the range of a Tower.
		 */
		bool CanUpgradeTowerRange(int p_playerNumber);

		/**
		 * @brief	Returns whether or not the player with player number p_playerNumber
					is able to upgrade the damage of a Tower.
		 *
		 * @author	Michel van Os.
		 * @param	p_playerNumber The number of the player to check if his score
					is high enough to upgrade the damage of a Tower.
		 * @return	Whether or not the player with p_playerNumber is able to upgrade
					the damage of a Tower.
		 */
		bool CanUpgradeTowerDamage(int p_playerNumber);

		/**
		 * @brief	Sets the score of the player with player number p_playerNumber.

		 * @author	Michel van Os.
		 * @param	p_playerNumber The number of the player to change the score of.
		 * @param	p_score The new score of the player.
		 */
		void SetPlayerScore(int p_playerNumber, int p_score);
		
		/**
		 * @brief	Resets the score of the player with player number p_playerNumber
		 *			to the default player score.
		 *
		 * @author	Michel van Os.
		 * @param	p_playerNumber The number of the player to reset the score of.
		 */
		void ResetPlayerScore(int p_playerNumber);

		/**
		 * @brief	Adds the amounts of points for the player with player number
		 *			p_playerNumber for when a Creature reached the Castle.
		 *
		 * @author	Michel van Os.
		 * @param	p_playerNumber The number of the player to change the score of.
		 */
		void CastleReached(int p_playerNumber);

		/**
		 * @brief	Adds the amounts of points for the player with player number
		 *			p_playerNumber for when a pencil is bought by the attacker.
		 *
		 * @author	Michel van Os.
		 * @param	p_playerNumber The number of the player to change the score of.
		 */
		void PencilBought(int p_playerNumber);

		/**
		 * @brief	Adds the amounts of points for the player with player number
		 *			p_playerNumber for when a Creature is killed.
		 *
		 * @author	Michel van Os.
		 * @param	p_playerNumber The number of the player to change the score of.
		 */
		void CreatureKilled(int p_playerNumber);

		/**
		 * @brief	Adds the amounts of points for the player with player number
		 *			p_playerNumber for when a Tower is created.
		 *
		 * @author	Michel van Os.
		 * @param	p_playerNumber The number of the player to change the score of.
		 */
		void TowerCreated(int p_playerNumber);

		/**
		 * @brief	Adds the amounts of points for the player with player number
		 *			p_playerNumber for when a Tower is destroyed.
		 *
		 * @author	Michel van Os.
		 * @param	p_playerNumber The number of the player to change the score of.
		 */
		void TowerDestroyed(int p_playerNumber);

		/**
		 * @brief	Adds the amounts of points for the player with player number
		 *			p_playerNumber for when the speed of a Tower is upgraded.
		 *
		 * @author	Michel van Os.
		 * @param	p_playerNumber The number of the player to change the score of.
		 */
		void TowerIncreasedSpeed(int p_playerNumber);

		/**
		 * @brief	Adds the amounts of points for the player with player number
		 *			p_playerNumber for when the range of a Tower is upgraded.
		 *
		 * @author	Michel van Os.
		 * @param	p_playerNumber The number of the player to change the score of.
		 */
		void TowerIncreasedRange(int p_playerNumber);

		/**
		 * @brief	Adds the amounts of points for the player with player number
		 *			p_playerNumber for when the damage of a Tower is upgraded.
		 *
		 * @author	Michel van Os.
		 * @param	p_playerNumber The number of the player to change the score of.
		 */
		void TowerIncreasedDamage(int p_playerNumber);

	private:
		int m_playerPoints[2];
		int m_playerPointsDefault[2];
		
		int m_pencilsDefault;
		int m_pencilsOwned;

		int m_pointsCastleReached;
		int m_pointsPencilBought;
		int m_pointsCreatureKilled;
		int m_pointsTowerCreated;
		int m_pointsTowerDestroyed;
		int m_pointsTowerIncreasedSpeed;
		int m_pointsTowerIncreasedRange;
		int m_pointsTowerIncreasedDamage;
	};
}

#endif