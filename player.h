#ifndef PLAYER_H_
#define PLAYER_H_

#include "scene_node.h"

namespace game {
	class Player : public SceneNode
	{
	public:
		Player(const std::string name, const Resource *geometry, const Resource *material);
		~Player();

		glm::quat GetForward();

		void Accelerate();
		void Deccelerate();
		void RotateLeft();
		void RotateRight();
		void Rise();
		void Fall();

		void Update();

		void BeginLaser();
		void EndLaser();

	private:
		glm::quat forward_ = glm::angleAxis(0/glm::pi<float>(), glm::vec3(0.0, 0.0, 1.0));

		float speed_ = 1;

		SceneNode* laser;
	};
}

#endif // PLAYER_H_