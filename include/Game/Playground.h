#ifndef __GAME__PLAYGROUND__H__
#define __GAME__PLAYGORUND__H__

#include "Path.h" 
#include "PathBuilder.h"
#include "Tower.h"
#include "PathFollower.h"

#include <irrlicht.h>

namespace Game
{
	/**
	* @brief	Playground is an area the game is played on
	*
	*			The playground consist of Tower(s)  Monster(s)  and a Path
	* @author	Michel van Os
	* @author	Menno Postma
	*/
	class Playground
	{
	public:
		Playground(irr::scene::ISceneManager* p_sceneManager);
		~Playground();

		void Initialize(irr::scene::ISceneManager* p_sceneManager);
		void Update(float p_deltaTime);
		void Render(irr::scene::ISceneManager*);

		bool SetupPath(
				irr::core::vector3df* p_points1,
				irr::core::vector3df* p_points2,
				int p_amount,
				float p_range,
				irr::core::vector3df p_pointBegin,
				irr::core::vector3df p_pointEnd
			);

	private:
		PathBuilder* m_pathBuilder;
		Path* m_path;

		std::list<Tower*> m_towers;
		std::list<PathFollower*> m_pathFollowers;

		float CalculateSpeedScale();
	};
}

#endif