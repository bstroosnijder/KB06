#ifndef __GAME__GAMEMANAGER__H__
#define __GAME__GAMEMANAGER__H__

#include "Defines.h"
#include "GameListener.h"
#include "GameStatus.h"
#include "PlayerType.h"
#include "ScoreManager.h"
#include "Playground.h"
#include "DeltaTimer.h"
#include "EventHandler.h"
#include "Utility/Logger.h"

#include <irrlicht.h>

namespace Game
{
	/**
	 * @brief	
	 * @todo	Write ALL comments (which is ALOT!!!!)
	 *			
	 * @author	Alex Hodes, Leon van Egmond
	 */
	class GameManager : public GameListener, UserInputListener
	{
	public:
	   /**
		* @brief	constructs the gamemanager
		* @param	p_device		the rendering videodevice
		* @param	p_resolution	the window resolution	
		*/
		GameManager(irr::IrrlichtDevice* p_device, irr::core::dimension2du p_resolution);

	   /**
		* @brief	destructs the gamemanager
		*/
		~GameManager();

	   /**
	    * @brief	This will stop the game and closes the graphics device
		*/
		void StopGame();

	   /**
	    * @brief	The gametick will occur every update cycle of the program and it will update and render the game
		*/
		void GameTick();

	   /**
	    * @brief	Get the Event handler instance for the game manager
		* @return	Returns the instance of the Event handler.
		*/
		irr::IEventReceiver* GetEventReceiver();

	   /**
	    * @brief	Adds the captured image of the camera to the video driver and returns it as a texture
		* @return	Returns an irrlicht ITexture object containing the captured image of the camera
		*/
		irr::video::ITexture* GetCameraTexture();

	   /**
	    * @brief	Sets the vertical position of the camera
		* @param	p_cameraHeight		The new y-coördinate of the camera
		*/
		void SetCameraHeight(float p_cameraHeight);

	   /**
	    * @brief	Sets the game length.
		* @param	p_gameLength	Width of the game dimensions
		* @see		Playground::UpdateGameScale
		*/
		void SetGameLength(float p_gameLength);

	   /**
	    * @brief	Sets the size of the image which the camera captures
		* @param	p_captureResolution	The size of the image to capture
		*/
		void SetCaptureResolution(irr::core::dimension2du p_captureResolution);

	   /**
	    * @brief	Gets the root scene node from the irrlicht scene manager
		* @return	Returns an irrlicht ISceneNode object of the root scene node
		*/
		irr::scene::ISceneNode* GetRootSceneNode();

	   /**
	    * @brief	Draws the texture of captured image of the camera to the screen
		*/
		void DrawCameraTexture();

	   /**
	    * @brief	Gets the projection matrix
		* @return	Returns the camera's projection matrix
		*/
		irr::core::matrix4 GetCameraProjectionMatrix();

	   /**
	    * @brief	Determines if the game is scanning for pencil coördinates
		* @return	Returns true if the game is scanning for pencil coördinates
		*/
		bool IsLookingForPencilCoords();

	   /**
	    * @brief	Sets the pencil coördinates and sets up the pathbuilder
		* @param	m_points1	A list of starting points of type vector3df
		* @param	m_points2	A list of ending points of type vector3df
		* @param	p_amount	The amount of points in the list
		* @see		Playground::SetupPath
		*/
		void SetPencilCoords(
				irr::core::vector3df* p_points1,
				irr::core::vector3df* p_points2,
				int p_amount);

	   /**
	    * @brief	Notifies the videodriver that the scene has begun
		*/
		void BeginScene();

	   /**
	    * @brief	Notifies the videodriver that the scene has ended
		*/
		void EndScene();
		
		
	   /**
	    * @brief	Event handler for when a creature has spawned
		*/
		void OnCreatureSpawned();

	   /**
	    * @brief	Event handler for when a creature has reached the castle
		*/
		void OnCreatureReachedCastle();

	   /**
	    * @brief	Event handler for when a creature has been killed
		*/
		void OnCreatureKilled();

	   /**
	    * @brief	Event handler for when a wave has ended
		*/
		void OnWaveEnded();

	   /**
	    * @brief	Event handler for when the user has pressed the stop button
		*/
		void OnStopGame();

	   /**
	    * @brief	Event handler for when the user has pressed the start wave button
		*/
		void OnStartWave();

	   /**
	    * @brief	Event handler for when the user may place pencils on the table
		*/
		void OnPlacePencils();

	   /**
	    * @brief	Event handler for when the game captures the pencils on the table
		*/
		void OnCapturePencils();

	   /**
	    * @brief	Event handler for when the user buys a pencil
		*/
		void OnBuyPencil();

	   /**
	    * @brief	Event handler for when the user may place towers on the playground
		*/
		void OnPlaceTowers();

	   /**
	    * @brief	Event handler for when the user has placed a tower on the playground
		* @param	p_position	The position of the tower
		*/
		void OnTowerCreate(irr::core::vector2di p_position);

	   /**
	    * @brief	Event handler for when the user has destroyed a tower on the playground
		* @param	p_position	The position of the tower
		*/
		void OnTowerDestroy(irr::core::vector2di p_position);

	   /**
	    * @brief	Event handler for when the user wants to upgrade the speed of a tower
		* @param	p_position	The position of the tower
		*/
		void OnTowerUpgradeSpeed(irr::core::vector2di p_position);

	   /**
	    * @brief	Event handler for when the user wants to upgrade the range of a tower
		* @param	p_position	The position of the tower
		*/
		void OnTowerUpgradeRange(irr::core::vector2di p_position);

	   /**
	    * @brief	Event handler for when the user wants to upgrade the damage of a tower
		* @param	p_position	The position of the tower
		*/
		void OnTowerUpgradeDamage(irr::core::vector2di p_position);

	   /**
	    * @brief	Get the height of the game
		* @return	Returns the height of the playground.
		*/
		float GetGameHeight();

	private:
		irr::IrrlichtDevice* m_device;
		irr::core::dimension2du m_resolution;
		irr::core::dimension2du m_captureResolution;
		irr::scene::ISceneManager* m_sceneManager;
		irr::video::IVideoDriver* m_videoDriver;
		irr::scene::ICameraSceneNode* m_camera;
		irr::scene::ICameraSceneNode* m_cameraFPS;

		ScoreManager m_scoreManager;
		GameStatus m_gameStatus;
		PlayerType m_player1;
		Playground* m_playground;
		Gui* m_gui;
		EventHandler* m_eventHandler;
		DeltaTimer* m_deltaTimer;


		bool m_isLookingForPencilCoords;

		
		/**
		 * @brief	This will update the logic of the game
		 */
		void Update();

		/**
		 * @brief	This will render all scene nodes, the playground and the GUI
		 */
		void Render();

		/**
		 * @brief	Creates a camera and sets the starting position and lookat position.
		 */
		void SetupCamera();

	   /**
	    * @brief	Gets the number of the player depending of the player's type.
		*/
		int GetPlayerNumber(PlayerType p_playerType);
	};
}

#endif