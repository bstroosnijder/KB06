#ifndef __GAME__KERNEL__H__
#define __GAME__KERNEL__H__

#include <irrlicht.h>

/*
 * @brief	The game namespace contains all classes related to the game.
 * This will be used mainly as a container and might be subdivided into further namespaces when nessecary.
 * 
 * @author	Bas Stroosnijder
 */
namespace Game
{
	/*
	 * @brief	This class will help with the initialization of all the core systems that we need for the game to run properly.
	 * 
	 * @author	Bas Stroosnijder
	 */
	class Kernel
	{
	public:
		Kernel();
		~Kernel();
		void Cleanup();
		void Start();

	private:
		irr::IrrlichtDevice* m_device;
		irr::video::IVideoDriver* m_driver;
		irr::scene::ISceneManager* m_scene;

		void Setup();
	};
}

#endif