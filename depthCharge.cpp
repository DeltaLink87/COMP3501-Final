#include "depthCharge.h"

namespace game {

DepthCharge::DepthCharge(const std::string name, glm::vec3 pos, glm::quat orientation) : Attack(name, "MissileCylinder", "ObjectMaterial"){
	this->damage = 3;
	this->SetPosition(pos);
	this->SetOrientation(orientation);
	this->SetAcceleration(glm::vec3(0, -0.01, 0));
}


DepthCharge::~DepthCharge(){}
            
} // namespace game
