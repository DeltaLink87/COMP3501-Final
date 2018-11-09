#include "player.h"

namespace game {

	Player::Player(const std::string name, const Resource *geometry, const Resource *material) : SceneNode(name, geometry, material) {
		this->SetOrientation(glm::angleAxis(glm::pi<float>() / 2.0f, glm::vec3(1.0, 0.0, 0.0)));

		laser = new SceneNode(std::string("PlayerLaser"), geometry, material);
		laser->SetScale(glm::vec3(0.5, 100, 0.5));
		laser->SetPosition(glm::vec3(0, 102, 0));
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
		this->Rotate(glm::angleAxis(-glm::pi<float>() / 180, glm::vec3(0.0, 0.0, 1.0)));
	}

	void Player::RotateRight() {
		forward_ *= glm::angleAxis(glm::pi<float>() / 180, glm::vec3(0.0, 1.0, 0.0));
		this->Rotate(glm::angleAxis(glm::pi<float>() / 180, glm::vec3(0.0, 0.0, 1.0)));
	}

	void Player::Rise() {
		this->Translate(glm::vec3(0, 2, 0));
	}

	void Player::Fall() {
		this->Translate(glm::vec3(0, -3, 0));
	}

	void Player::Update() {
		this->Translate(glm::vec3(0, 0, speed_) * forward_);
	}

	void Player::BeginLaser() {
		this->AddChild(laser);
	}

	void Player::EndLaser() {
		this->RemoveChild(laser);
	}
}