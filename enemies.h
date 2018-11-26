#ifndef ENEMIES_H_
#define ENEMIES_H_

#include "scene_node.h"
#include "turret.h"
#include "scene_graph.h"

namespace game {
	class Enemies : public SceneNode
	{
	public:
		Enemies(const std::string name, const Resource *geometry, const Resource *material);
		~Enemies();
		int isDead;

		glm::quat GetForward();

		void Accelerate();
		void Deccelerate();
		void RotateLeft();
		void RotateRight();
		void Rise();
		void Fall();
		void TakeDamage();

		void Update();

		void BeginLaser();
		void EndLaser();
		Turret* addTurret(const std::string name, ResourceManager* rm);
		void removeTurret(SceneGraph scn);

	private:
		glm::quat forward_ = glm::angleAxis(0/glm::pi<float>(), glm::vec3(0.0, 0.0, 1.0));
		int health;
		int points;
		float speed_ = 1;

		SceneNode* laser;

		SceneNode* turret;

	};
}

#endif // ENEMIES_H_