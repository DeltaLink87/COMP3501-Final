#ifndef SUBMARINE_H_
#define TURRET_H_

#include "resource.h"
#include "enemy.h"
#include "resource_manager.h"
#include "player.h"
#include "bound.h"

namespace game {
	class Submarine : public Enemy
	{
	public:
		Submarine(const std::string name, ResourceManager* rm);
		~Submarine();

		void Update(void);

	private:
		SceneNode* propeller_;
		ParticleFountain* particleTrail;

		float subRotation_ = 0;
		float speed = 0;

		float coolDown = 0;
	};
}

#endif // TURRET_H_


