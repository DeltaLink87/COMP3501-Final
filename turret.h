#ifndef TURRET_H_
#define TURRET_H_

#include "resource.h"
#include "scene_node.h"
#include "resource_manager.h"
#include "player.h"
#include "bound.h"

namespace game {
	class Turret : public SceneNode
	{
	public:
		Turret(const std::string name, ResourceManager* rm);
		~Turret();

		int isDead = 1;
		void Update(void);
		void takeDamage();

		void setPlayer(Player* player);

		Bound getBounds() const;
		Attack* getNewAttack();

	private:

		SceneNode* body_;
		SceneNode* lowerCannon_;
		SceneNode* upperCannon_;

		Player* player = NULL;

		Bound bounds = Bound(glm::vec3(), glm::vec3(), 0.96);

		float turretRotation_ = 0;
		float cannonLevel_ = glm::pi<float>() / 2.0f;
		float cannonBarrelLength = 0;
		float rotationTimer = 0;

		float coolDown = 0;
		Attack* attack = NULL;
		int health = 10;

	};
}

#endif // TURRET_H_


