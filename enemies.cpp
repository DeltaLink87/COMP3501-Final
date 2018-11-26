#include "enemies.h"

namespace game {

	Enemies::Enemies(const std::string name, const Resource *geometry, const Resource *material) : SceneNode(name, geometry, material) {
		this->SetOrientation(glm::angleAxis(glm::pi<float>() / 2.0f, glm::vec3(1.0, 0.0, 0.0)));
		isDead = 1;

		laser = new SceneNode(std::string("PlayerLaser"), geometry, material);
		laser->SetScale(glm::vec3(0.5, 100, 0.5));
		laser->SetPosition(glm::vec3(0, 102, 0));


	}

	Enemies::~Enemies() {}

	glm::quat Enemies::GetForward() {
		return forward_;// *glm::vec3(0.0, 0.0, 1.0);
	}

	void Enemies::Accelerate() {
		speed_ += 0.1;
		if (speed_ > 5)
			speed_ = 5;
	}

	void Enemies::Deccelerate() {
		speed_ -= 0.1;
		if (speed_ < -1)
			speed_ = -1;
	}

	void Enemies::RotateLeft() {
		forward_ *= glm::angleAxis(-glm::pi<float>() / 180, glm::vec3(0.0, 1.0, 0.0));
		this->Rotate(glm::angleAxis(-glm::pi<float>() / 180, glm::vec3(0.0, 0.0, 1.0)));
	}

	void Enemies::RotateRight() {
		forward_ *= glm::angleAxis(glm::pi<float>() / 180, glm::vec3(0.0, 1.0, 0.0));
		this->Rotate(glm::angleAxis(glm::pi<float>() / 180, glm::vec3(0.0, 0.0, 1.0)));
	}

	void Enemies::Rise() {
		this->Translate(glm::vec3(0, 2, 0));
	}

	void Enemies::Fall() {
		this->Translate(glm::vec3(0, -3, 0));
	}

	void Enemies::Update() {
		this->Translate(glm::vec3(0, 0, speed_) * forward_);
	}

	void Enemies::BeginLaser() {
		this->AddChild(laser);
	}

	void Enemies::EndLaser() {
		this->RemoveChild(laser);
	}

	Turret* Enemies::addTurret(const std::string name, ResourceManager* rm) {

		Turret*turret = new Turret(name, rm);
		turret->SetPosition(glm::vec3(0, -125, 300));
		turret->SetScale(glm::vec3(10, 10, 10));
		return turret;
	}

	void Enemies::removeTurret(SceneGraph scn) {

		scn.RemoveNode(turret);
	}

	void Enemies::TakeDamage() {
		health -= 1;

		if (health <= 0) {
			isDead = 0;
		}
	}
}