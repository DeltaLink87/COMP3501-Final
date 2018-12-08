#ifndef MINE_H_
#define MINE_H_

#include "particle_system.h"
#include "resource.h"
#include "enemy.h"
#include "resource_manager.h"
#include "player.h"
#include "bound.h"

namespace game {
	class Mine : public Enemy
	{
	public:
		Mine(const std::string name, ResourceManager* rm);
		~Mine();

		void Update(void);

	private:
		float bobblingTimer = 0;
	};

	class MineAttack : public Attack
	{
	public:
		MineAttack(const std::string name, glm::vec3 pos);
		~MineAttack();

		void UpdateBounds();


		ParticleSystem* hitParticles(ResourceManager* resMan);

	private:
		float bobblingTimer = 0;
	};
}

#endif // TURRET_H_


