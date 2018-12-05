#include "pulse.h"

namespace game {

Pulse::Pulse(const std::string name, glm::vec3 pos, glm::vec3 movement, glm::quat orientation) : Attack(name, "MissileCylinder", "ObjectMaterial"){
	this->damage = 1;
	this->SetPosition(pos);
	this->SetMovment(glm::normalize(movement) * 2.0f);
	this->SetOrientation(orientation);
}


Pulse::~Pulse(){}
            
} // namespace game
