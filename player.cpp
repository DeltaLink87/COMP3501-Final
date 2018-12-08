#include "player.h"
#include "pulse.h"
#include "torpedo.h"
#include "depthCharge.h"

namespace game {

	Player::Player(const std::string name, ResourceManager* rm) : SceneNode(name, rm->GetResource("SubMesh"), rm->GetResource("ObjectMaterial"), rm->GetResource("SubTex"), rm->GetResource("LakeCubeMap")) {
		this->SetReflectivity(0.5f);
		this->SetOrientation(glm::angleAxis(glm::pi<float>() / 2.0f, glm::vec3(1.0, 0.0, 0.0)));
		this->SetScale(glm::vec3(0.5, 0.5, 0.5));
		bounds = Bound(glm::vec3(), glm::vec3(), 2 * 0.5);

		propeller_ = new SceneNode(name + "Propeller", rm->GetResource("PropellerMesh"), rm->GetResource("ObjectMaterial"), rm->GetResource("MetalTexture"));
		propeller_->SetJointPos(glm::vec3(-0.1025, 0.0, -0.1425));
		this->AddChild(propeller_);

		particleTrail = new ParticleFountain("PlayerSubTrail", rm->GetResource("BubbleCluster"), rm->GetResource("TrailMaterial"), rm->GetResource("BubbleTexture"), 1.0f);
		particleTrail->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
		particleTrail->SetBlending(true);
		this->AddChild(particleTrail);

		health = 20;
		points = 0;
	}

	Player::~Player() {
		delete propeller_;
		delete particleTrail;
	}

	glm::quat Player::GetForward() {
		return forward_;// *glm::vec3(0.0, 0.0, 1.0);
	}

	void Player::Accelerate() {
		speed_ += 0.1;
		if (speed_ > 1)
			speed_ = 1;
	}

	void Player::Deccelerate() {
		speed_ -= 0.1;
		if (speed_ < -0.5)
			speed_ = -0.5;
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
		this->Translate(glm::vec3(0, 0.5, 0));
	}

	void Player::GainPoint() {
		points += 1;
		std::printf("Players Points is at: %d\n", points);
	}

	void Player::Fall() {
		this->Translate(glm::vec3(0, -0.75, 0));
	}

	void Player::Update() {
		this->Translate(glm::vec3(0, 0, speed_) * forward_);
		bounds.setPositions(GetPosition() + GetOrientation() * glm::vec3(0, 7.0, 0) * GetScale(), GetPosition());
		propeller_->Rotate(glm::angleAxis(glm::pi<float>() * (speed_ * 0.25f), glm::vec3(0.0, 1.0, 0.0)));
		time();
	}

	void Player::fire() {
		if (attack != NULL)
			delete attack;

		if (fireType == 1) {
			attack = new Pulse("PlayerPulse", GetPosition() + (glm::vec3(0, 0, 12) * GetScale()) * forward_, glm::vec3(0, 0, 4) * forward_,
				glm::normalize(glm::angleAxis(glm::pi<float>() / 2.0f, glm::vec3(1.0, 0.0, 0.0) * forward_)));
		}
		else if (fireType == 2) {
			attack = new DepthCharge("PlayerMine", GetPosition() + (glm::vec3(0, -2, 0) * GetScale()), glm::normalize(glm::angleAxis(0.0f, glm::vec3(1.0, 0.0, 0.0) * forward_)));
		}
		else if (fireType == 3) {
			attack = new Torpedo("PlayerMissile", GetPosition() + (glm::vec3(0, 0, 9.5) * GetScale()) * forward_, glm::vec3(0, 0, 4) * forward_,
				glm::normalize(glm::angleAxis(-glm::pi<float>() / 2.0f, glm::vec3(1.0, 0.0, 0.0) * forward_)));
		}
	}

	void Player::changeFireType(int type) {
		fireType = type;
	}

	void Player::takeDamage(int dmg) {
		health -= dmg;
		std::printf("Players Health is at: %d\n", health);
	}

	bool Player::isDead() {
		return health <= 0;
	}

	Attack* Player::getNewAttack() {
		Attack* usedAttack = this->attack;
		this->attack = NULL;
		return usedAttack;
	}

	Bound Player::getBounds() const {
		return bounds;
	}

	void Player::time() {
		countDown -= 1.0 / 60.0; //increase time
		//std::printf("%f", countDown);
		if (countDown <= 10.0 && countDown >= 9.9) {
			std::printf("RUNNING OUT OF TIME! 10 SECONDS LEFT\n");

		}

		if (countDown <= 5.0 && countDown >= 4.9) {
			std::printf("RUNNING OUT OF TIME! 5 SECONDS LEFT\n");

		}

		if (countDown <= 0.0 ) {
			std::printf("TIMES UP! restart to play again!\n");
			health = 0;

			std::printf("YOUR SCORE is at: %d\n", points);

		}
	}

}