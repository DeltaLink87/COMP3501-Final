#include "torpedo.h"

namespace game {

Torpedo::Torpedo(const std::string name, glm::vec3 pos, glm::vec3 movement, glm::quat orientation) : Attack(name, "MissileCylinder", "ObjectMaterial"){
	this->damage = 2;
	this->SetPosition(pos);
	this->SetMovment(glm::normalize(movement) * 2.0f);
	this->SetOrientation(orientation);
}


Torpedo::~Torpedo(){}
            
} // namespace game
