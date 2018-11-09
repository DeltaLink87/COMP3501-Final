#ifndef TURRET_H_
#define TURRET_H_

#include "resource.h"
#include "scene_node.h"
#include "resource_manager.h"

namespace game {
	class Turret : public SceneNode
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
		float cannonLevel_ = 0;
		float cannonBarrelLength = 0;
	};
}

#endif // TURRET_H_


