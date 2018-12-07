#include "depthCharge.h"

namespace game {

float scale = 0.2f;

DepthCharge::DepthCharge(const std::string name, glm::vec3 pos, glm::quat orientation) : Attack(name, "MineMesh", "ObjectMaterial", "MetalTexture"){
	this->damage = 3;
	this->SetPosition(pos);
	this->SetOrientation(orientation);
	this->SetAcceleration(glm::vec3(0, -0.01, 0));
	bounds = Bound(glm::vec3(), glm::vec3(), 1.0f * scale);
}


DepthCharge::~DepthCharge(){}

void DepthCharge::UpdateBounds() {
	bounds.setPositions(position + glm::vec3(0, 2.9999, 0) * scale, position + glm::vec3(0, 3.0001, 0) * scale);
}

SceneNode* DepthCharge::createSceneNode(ResourceManager* resMan) {
	SceneNode* node = Attack::createSceneNode(resMan);
	node->SetScale(glm::vec3(scale, scale, scale));
	return node;
}

ParticleSystem* DepthCharge::hitParticles(ResourceManager* resMan) {
	ParticleSystem* p = new ParticleSystem(name + "Explosion", resMan->GetResource("BubbleCluster"), resMan->GetResource("ExplosionMaterial"), resMan->GetResource("FireTexture"), 1.0f);
	p->SetBlending(true);
	//p->SetScale(glm::vec3(10, 10, 10));
	p->SetPosition(position);
	return p;
}
            
} // namespace game
