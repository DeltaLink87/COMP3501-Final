#include "depthCharge.h"

namespace game {

float scale = 0.2f;

DepthCharge::DepthCharge(const std::string name, glm::vec3 pos, glm::quat orientation) : Attack(name, "MineMesh", "ObjectMaterial", "MetalTexture"){
	this->damage = 3;
	this->SetPosition(pos);
	this->SetOrientation(orientation);
	this->SetAcceleration(glm::vec3(0, -0.01, 0));
	bounds = Bound(glm::vec3(), glm::vec3(), 3.0f * scale);
}


DepthCharge::~DepthCharge(){}

void DepthCharge::UpdateBounds() {
	bounds.setPositions(position + glm::vec3(0, 0.05, 0), position + glm::vec3(0, -0.05, 0));
}

SceneNode* DepthCharge::createSceneNode(ResourceManager* resMan) {
	SceneNode* node = Attack::createSceneNode(resMan);
	node->SetScale(glm::vec3(scale, scale, scale));
	return node;
}
            
} // namespace game
