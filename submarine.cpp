#include "submarine.h"
#include <math.h>
#include <iostream>
#include "torpedo.h"

namespace game {

Submarine::Submarine(const std::string name, ResourceManager* rm) : Enemy(name + "Submarine", rm->GetResource("EnemySubMesh"), rm->GetResource("ObjectMaterial"), rm->GetResource("enemyTex")) {
	this->SetOrientation(glm::angleAxis(glm::pi<float>() / 2.0f, glm::vec3(1.0, 0.0, 0.0)));
	this->SetScale(glm::vec3(0.5, 0.5, 0.5));
	bounds = Bound(glm::vec3(), glm::vec3(), 2 * 0.5);
	this->SetRoughness(0.25f);

	propeller_ = new SceneNode(name + "Propeller", rm->GetResource("PropellerMesh"), rm->GetResource("ObjectMaterial"), rm->GetResource("MetalTexture"));
	propeller_->SetJointPos(glm::vec3(-0.1025, 0.0, -0.1425));
	this->AddChild(propeller_);

	particleTrail = new ParticleFountain("PlayerSubTrail", rm->GetResource("BubbleCluster"), rm->GetResource("TrailMaterial"), rm->GetResource("BubbleTexture"), 1.0f);
	particleTrail->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	particleTrail->SetBlending(true);
	this->AddChild(particleTrail);

	health = 2;
}

Submarine::~Submarine() {
	delete propeller_;
	if (particleTrail)
		delete particleTrail;
}


void Submarine::Update() {
	float prevRotation = subRotation_;
	if (player == NULL) {
		subRotation_ += glm::pi<float>() / 18.0f;
		if (speed < 0.25);
			speed += 0.05;
	}
	else {
		glm::vec3 playerPos = player->GetPosition();

		float playerDis = glm::distance(playerPos, GetPosition());
		if (playerDis < 200) {
			glm::vec3 subToPlayerVec = glm::normalize(playerPos - GetPosition());
			float test = glm::pi<float>();
			float subRotDif = (atan((float)(subToPlayerVec.x / subToPlayerVec.z)) + (subToPlayerVec.z < 0 ? glm::pi<float>() : 0)) - subRotation_;
			if (subRotDif > glm::pi<float>())
				subRotDif -= glm::pi<float>() * 2;
			if (abs(subRotDif) < 0.1)
				subRotation_ += subRotDif;
			else subRotation_ += 0.1 * (subRotDif > 0 ? 1 : -1);
			subRotation_ = fmod(subRotation_ + glm::pi<float>() / 2, glm::pi<float>() * 2) - glm::pi<float>() / 2;

			float subHeightDif = playerPos.y - GetPosition().y;
			if (abs(subHeightDif) > 0.5)
				this->Translate(glm::vec3(0.0, 0.5, 0.0) * (subHeightDif > 0 ? 1.0f : -1.0f));
			else
				this->Translate(glm::vec3(0.0, subHeightDif, 0.0));

			if (subHeightDif < 0.5 && subHeightDif > -0.5 && subRotDif < 0.05 && subRotDif > -0.05 && coolDown <= 0) {
				glm::vec3 attDirRelToSub = glm::vec3(0.0, 0.0, 10.0) * GetScale() * glm::angleAxis(-subRotation_, glm::vec3(0.0, 1.0, 0.0));
				
				glm::vec3 attackPosToPlayer = glm::normalize(playerPos - (GetPosition() + attDirRelToSub));

				attack = new Torpedo("EnemyMissile", GetPosition() + attDirRelToSub, glm::normalize(attackPosToPlayer) * 2.0f,
					glm::normalize(glm::angleAxis(subRotation_, glm::vec3(0.0, 1.0, 0.0)) * glm::angleAxis(-glm::pi<float>() / 2.0f, glm::vec3(1.0, 0.0, 0.0))));
				attack->SetDamage(1);
				coolDown = 120;
			}

			if (playerDis < 50 && speed > 0) {
				speed -= 0.05;
			}

		}
		if (coolDown > 0)
			coolDown--;
	}

	if (speed < 0)
		speed = 0;

	this->SetOrientation(glm::angleAxis(glm::pi<float>() / 2.0f, glm::vec3(1.0, 0.0, 0.0)) * glm::angleAxis(-subRotation_, glm::vec3(0.0, 0.0, 1.0)));
	this->Translate(glm::normalize(glm::angleAxis(subRotation_, glm::vec3(0.0, 1.0, 0.0)) * glm::vec3(0.0, 0.0, 1.0)) * speed);

	bounds = Bound(GetPosition() + GetOrientation() * glm::vec3(0, 7.0, 0) * GetScale(), GetPosition(), 1.5 * GetScale().x);
	bounds.setPositions(GetPosition() + GetOrientation() * glm::vec3(0, 7.0, 0) * GetScale(), GetPosition());

	propeller_->Rotate(glm::angleAxis(glm::pi<float>() / 4, glm::vec3(0.0, 1.0, 0.0)));
}

}

