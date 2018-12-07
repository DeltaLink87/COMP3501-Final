#include "turret.h"
#include <math.h>
#include <iostream>
#include "torpedo.h"

namespace game {

Turret::Turret(const std::string name, ResourceManager* rm) : Enemy(name + "Tower", rm->GetResource("TurTowerCube"), rm->GetResource("ObjectMaterial"), rm->GetResource("MetalTexture")) {
	body_ = new SceneNode(name + "Body", rm->GetResource("TurBodyCylinder"), rm->GetResource("ObjectMaterial"), rm->GetResource("DiceTexture"));
	lowerCannon_ = new SceneNode(name + "Lower", rm->GetResource("TurLowerCylinder"), rm->GetResource("ObjectMaterial"), rm->GetResource("MetalTexture"));
	upperCannon_ = new SceneNode(name + "Upper", rm->GetResource("TurUpperCylinder"), rm->GetResource("ObjectMaterial"), rm->GetResource("MetalTexture"));

	this->AddChild(body_);
	body_->AddChild(lowerCannon_);
	lowerCannon_->AddChild(upperCannon_);

	body_->SetScale(glm::vec3(1.2, 1.2, 1.2));
	body_->SetPosition(glm::vec3(0, 0.75, 0));
	lowerCannon_->SetPosition(glm::vec3(0, 0.5, 0.65));
	lowerCannon_->SetJointPos(glm::vec3(0, -0.5, 0));
	lowerCannon_->SetOrientation(glm::angleAxis(glm::pi<float>() / 2.0f, glm::vec3(1.0, 0.0, 0.0)));
	upperCannon_->SetPosition(glm::vec3(0, 0.5, 0.0));

	health = 10;
}

Turret::~Turret() {
	delete upperCannon_;
	delete lowerCannon_;
	delete body_;
}


void Turret::Update() {
	if (player == NULL) {
		rotationTimer += 0.1;
		turretRotation_ = rotationTimer / 2;
		cannonLevel_ = -1 * (float)(0.9*sin(rotationTimer)) + glm::pi<float>() / 2.0f;
		cannonBarrelLength = 0.15f * sin(rotationTimer * 1.2f) + 0.5;
	}
	else {
		glm::vec3 playerPos = player->GetPosition();

		float playerDis = glm::distance(playerPos, GetPosition());
		if (playerDis < 300) {
			glm::vec3 towerToPlayerVec = glm::normalize(playerPos - GetPosition());
			float test = glm::pi<float>();
			float towerRotDif = (atan((float)(towerToPlayerVec.x / towerToPlayerVec.z)) + (towerToPlayerVec.z < 0 ? glm::pi<float>() : 0)) - turretRotation_;
			if (towerRotDif > glm::pi<float>())
				towerRotDif -= glm::pi<float>() * 2;
			if (abs(towerRotDif) < 0.01)
				turretRotation_ += towerRotDif;
			else turretRotation_ += 0.01 * (towerRotDif > 0 ? 1 : -1);
			turretRotation_ = fmod(turretRotation_ + glm::pi<float>() / 2, glm::pi<float>() * 2) - glm::pi<float>() / 2;

			float cannonLevelDif =  (-atan((float)(towerToPlayerVec.y / (sqrt(pow(towerToPlayerVec.x, 2) + pow(towerToPlayerVec.z, 2))))) + glm::pi<float>() / 2) - cannonLevel_;
			if (cannonLevelDif > glm::pi<float>())
				cannonLevelDif -= glm::pi<float>() * 2;
			if (abs(cannonLevelDif) < 0.01)
				cannonLevel_ += cannonLevelDif;
			else cannonLevel_ += 0.01 * (cannonLevelDif > 0 ? 1 : -1);
			if (cannonLevel_ > glm::pi<float>() * 0.95)
				cannonLevel_ = glm::pi<float>() * 0.95;
			if (cannonLevel_ < glm::pi<float>() * 0.05)
				cannonLevel_ = glm::pi<float>() * 0.05;

			if (cannonLevelDif < 0.05 && cannonLevelDif > -0.05 && towerRotDif < 0.05 && towerRotDif > -0.05 && coolDown <= 0) {
				glm::vec3 attDirRelToTurret = (glm::vec3(0, 0, 0.65) * glm::angleAxis(turretRotation_, glm::vec3(0.0, 1.0, 0.0)) +
					glm::vec3(0, 3, 0) * glm::angleAxis(cannonLevel_, glm::vec3(1.0, 0.0, 0.0)) * glm::angleAxis(turretRotation_, glm::vec3(0.0, 1.0, 0.0))) * GetScale() * glm::vec3(1, 1, -1);
				
				glm::vec3 attackPosToPlayer = glm::normalize(playerPos - (GetPosition() + glm::vec3(0, 0.5, 0) + attDirRelToTurret));

				attack = new Torpedo("EnemyMissile", GetPosition() + glm::vec3(0, 0.5, 0) + attDirRelToTurret, glm::normalize(attackPosToPlayer) * 2.0f,
					glm::normalize(glm::angleAxis(turretRotation_, glm::vec3(0.0, 1.0, 0.0)) * glm::angleAxis(cannonLevel_ + glm::pi<float>(), glm::vec3(1.0, 0.0, 0.0))));
				attack->SetDamage(1);
				coolDown = 60;
			}
		}
		cannonBarrelLength = 0.8 - 0.3 * ((coolDown > 50 ? coolDown-50 : 0)/10.0);
		if (coolDown > 0)
			coolDown--;
	}


	bounds = Bound(GetPosition() + glm::vec3(0, 0.5, 0) * GetScale(), GetPosition() + glm::vec3(0, -1.25, 0) * GetScale(), 1 * GetScale().x);
	//bounds.setPositions(this->GetPosition() + glm::vec3(0, -0.5, 0) * this->GetScale(), this->GetPosition() + glm::vec3(0, 1.5, 0) * this->GetScale());
	body_->SetOrientation(glm::angleAxis(turretRotation_, glm::vec3(0.0, 1.0, 0.0)));
	lowerCannon_->SetOrientation(glm::angleAxis(cannonLevel_, glm::vec3(1.0, 0.0, 0.0)));
	upperCannon_->SetPosition(glm::vec3(0, cannonBarrelLength, 0.0));
}

}

