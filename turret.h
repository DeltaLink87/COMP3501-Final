#ifndef TURRET_H_
#define TURRET_H_

#include "resource.h"
#include "enemy.h"
#include "resource_manager.h"
#include "player.h"
#include "bound.h"

namespace game {
	class Turret : public Enemy
	{
	public:
		Turret(const std::string name, ResourceManager* rm);
		~Turret();

		void Update(void);

	private:

		SceneNode* body_;
		SceneNode* lowerCannon_;
		SceneNode* upperCannon_;
		float turretRotation_ = 0;
		float cannonLevel_ = glm::pi<float>() / 2.0f;
		float cannonBarrelLength = 0;
		float rotationTimer = 0;

		float coolDown = 0;
	};
}

#endif // TURRET_H_


