#include "turret.h"

namespace game {

Turret::Turret(const std::string name, ResourceManager* rm) : SceneNode(name + "Tower", rm->GetResource("TurTowerCube"), rm->GetResource("ObjectMaterial"), rm->GetResource("MetalTexture")) {
	body_ = new SceneNode(name + "Body", rm->GetResource("TurBodyCylinder"), rm->GetResource("ObjectMaterial"), rm->GetResource("DiceTexture"));
	lowerCannon_ = new SceneNode(name + "Lower", rm->GetResource("TurLowerCylinder"), rm->GetResource("ObjectMaterial"), rm->GetResource("MetalTexture"));
	upperCannon_ = new SceneNode(name + "Upper", rm->GetResource("TurUpperCylinder"), rm->GetResource("ObjectMaterial"), rm->GetResource("MetalTexture"));

	this->AddChild(body_);
	body_->AddChild(lowerCannon_);
	lowerCannon_->AddChild(upperCannon_);

	//body_->SetScale(glm::vec3(5.0, 5.0, 5.0));
	body_->SetPosition(glm::vec3(0, 0.75, 0));
	lowerCannon_->SetPosition(glm::vec3(0, 0.5, 0.65));
	lowerCannon_->SetJointPos(glm::vec3(0, -0.5, 0));
	lowerCannon_->SetOrientation(glm::angleAxis(glm::pi<float>() / 2.0f, glm::vec3(1.0, 0.0, 0.0)));
	upperCannon_->SetPosition(glm::vec3(0, 0.5, 0.0));
}

Turret::~Turret() {}


void Turret::Update() {
	turretRotation_ += 0.1;
	cannonLevel_ += 0.1;
	cannonBarrelLength += 0.1;

	body_->SetOrientation(glm::angleAxis(turretRotation_ / 2, glm::vec3(0.0, 1.0, 0.0)));
	lowerCannon_->SetOrientation(glm::angleAxis(-1 * (float)(0.9*sin(cannonLevel_)) + glm::pi<float>() / 2.0f, glm::vec3(1.0, 0.0, 0.0)));
	upperCannon_->SetPosition(glm::vec3(0, 0.15f * sin(cannonBarrelLength * 1.2f) +  0.5, 0.0));
	
}

}

