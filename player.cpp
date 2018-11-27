#include "player.h"

namespace game {

	Player::Player(const std::string name, const Resource *geometry, const Resource *material) : SceneNode(name, geometry, material) {
		this->SetOrientation(glm::angleAxis(glm::pi<float>() / 2.0f, glm::vec3(1.0, 0.0, 0.0)));

		health = 20;
		points = 0;
		isDead = 1;
	}

	Player::~Player() {}

	glm::quat Player::GetForward() {
		return forward_;// *glm::vec3(0.0, 0.0, 1.0);
	}

	void Player::Accelerate() {
		speed_ += 0.1;
		if (speed_ > 5)
			speed_ = 5;
	}

	void Player::Deccelerate() {
		speed_ -= 0.1;
		if (speed_ < -1)
			speed_ = -1;
	}

	void Player::RotateLeft() {
		forward_ *= glm::angleAxis(-glm::pi<float>() / 180, glm::vec3(0.0, 1.0, 0.0));
		forward_ = glm::normalize(forward_);
		this->Rotate(glm::angleAxis(-glm::pi<float>() / 180, glm::vec3(0.0, 0.0, 1.0)));
	}

	void Player::RotateRight() {
		forward_ *= glm::angleAxis(glm::pi<float>() / 180, glm::vec3(0.0, 1.0, 0.0));
		forward_ = glm::normalize(forward_);
		this->Rotate(glm::angleAxis(glm::pi<float>() / 180, glm::vec3(0.0, 0.0, 1.0)));
	}

	void Player::Rise() {
		this->Translate(glm::vec3(0, 2, 0));
	}

	void Player::GainPoint() {
		points += 1;
		std::printf("Players Points is at: %d\n", points);
	}

	void Player::Fall() {
		this->Translate(glm::vec3(0, -3, 0));
	}

	void Player::Update() {
		this->Translate(glm::vec3(0, 0, speed_) * forward_);
		bounds.setPositions(GetPosition() + glm::vec3(0, 0, 1) * forward_ * GetScale(), GetPosition() + glm::vec3(0, 0, -1) * forward_ * GetScale());
	}

	void Player::fire() {
		if (attack != NULL)
			delete attack;

		if (fireType == 1) {
			attack = new Attack("PlayerMissile", "MissileCylinder", "ObjectMaterial");
			attack->SetPosition(GetPosition() + glm::vec3(0, 0, 1) * forward_);
			attack->SetOrientation(glm::normalize(glm::angleAxis(glm::pi<float>() / 2.0f, glm::vec3(1.0, 0.0, 0.0) * forward_)));
			attack->SetMovment(glm::vec3(0, 0, 4) * forward_);
		}
		else if (fireType == 2) {
			attack = new Attack("PlayerMine", "MissileCylinder", "ObjectMaterial");
			attack->SetPosition(GetPosition() + glm::vec3(0, -3, 0));
			attack->SetOrientation(glm::normalize(glm::angleAxis(glm::pi<float>() / 2.0f, glm::vec3(1.0, 0.0, 0.0) * forward_)));
			attack->SetAcceleration(glm::vec3(0, -0.01, 0));
		}
	}

	void Player::changeFireType(int type) {
		fireType = type;
	}

	void Player::takeDamage() {
		health -= 1;
		std::printf("Players Health is at: %d\n", health);

		if (health <= 0) {
			isDead = 0;
		}
	}

	Attack* Player::getNewAttack() {
		Attack* usedAttack = this->attack;
		this->attack = NULL;
		return usedAttack;
	}

	Bound Player::getBounds() const {
		return bounds;
	}
}