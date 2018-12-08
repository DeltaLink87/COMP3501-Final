#include "pulse.h"
#include <iostream>

namespace game {

Pulse::Pulse(const std::string name, glm::vec3 pos, glm::vec3 movement, glm::quat orientation) : Attack(name, "PulseCluster", "PulseMaterial", "BubbleTexture"){
	this->damage = 1;
	this->SetPosition(pos);
	this->SetMovment(glm::normalize(movement) * 2.0f);
	this->SetOrientation(orientation);
	Bound bounds = Bound(glm::vec3(), glm::vec3(), 2);
}


Pulse::~Pulse(){}

SceneNode* Pulse::createSceneNode(ResourceManager* resMan) {
	if (node != NULL)
		delete node;
	
	node = new ParticleFountain(name, resMan->GetResource(geoName), resMan->GetResource(matName), resMan->GetResource(texName), 1.0f);
	node->SetPosition(position);
	//node->SetOrientation(glm::angleAxis(glm::pi<float>() / 2.0f, glm::vec3(1.0, 0.0, 0.0)) * orientation);
	node->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
	node->SetBlending(true);

	return node;
}
            
} // namespace game
