#ifndef PLAYER_H_
#define PLAYER_H_

#include "scene_node.h"
#include "attack.h"
#include "particle_fountain.h"

namespace game {
	class Player : public SceneNode
	{
	public:
		Player(const std::string name, ResourceManager* rm);
		~Player();

		glm::quat GetForward();

		void Accelerate();
		void Deccelerate();
		void RotateLeft();
		void RotateRight();
		void Rise();
		void Fall();

		void Update();
		void GainPoint();
		void fire();
		void takeDamage(int dmg);
		void changeFireType(int type);
		Attack* getNewAttack();
		Bound getBounds() const;
		bool isDead();
		void time();

	private:
		SceneNode* propeller_;
		ParticleFountain* particleTrail;

		double countDown = 20;


		glm::quat forward_ = glm::angleAxis(0/glm::pi<float>(), glm::vec3(0.0, 0.0, 1.0));

		float speed_ = .5;

		int fireType = 1;

		Attack* attack = NULL;
		Bound bounds = Bound(glm::vec3(), glm::vec3(), 2);

		int health = 10;
		int points = 0;

	};
}

#endif // PLAYER_H_