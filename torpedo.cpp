#include "torpedo.h"

namespace game {

Torpedo::Torpedo(const std::string name, glm::vec3 pos, glm::vec3 movement, glm::quat orientation) : Attack(name, "TorpedoMesh", "ObjectMaterial", "TorpedoTex"){
	this->damage = 2;
	this->SetPosition(pos);
	this->SetMovment(glm::normalize(movement) * 2.0f);
	this->SetOrientation(orientation);
	bounds = Bound(glm::vec3(), glm::vec3(), 2);
}


Torpedo::~Torpedo(){
	if (particleTrail)
		delete particleTrail;
}

void Torpedo::UpdateBounds() {
	bounds.setPositions(position + orientation * glm::vec3(0, -1.5, 0), position + orientation * glm::vec3(0, -2.5, 0));
}

void Torpedo::Update() {
	Attack::Update();
}

SceneNode* Torpedo::createSceneNode(ResourceManager* resMan) {
	SceneNode* node = Attack::createSceneNode(resMan);

	particleTrail = new ParticleFountain("PlayerSubTrail", resMan->GetResource("TrailCluster"), resMan->GetResource("TrailMaterial"), resMan->GetResource("BubbleTexture"), 1.0f);
	particleTrail->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	particleTrail->SetPosition(glm::vec3(0, 2.5, 0));
	particleTrail->SetOrientation(glm::angleAxis(glm::pi<float>(), glm::vec3(1, 0, 0)));
	particleTrail->SetBlending(true);
	node->AddChild(particleTrail);

	return node;
}
            
ParticleSystem* Torpedo::hitParticles(ResourceManager* resMan) {
	ParticleSystem* p = new ParticleSystem(name + "Explosion", resMan->GetResource("BubbleCluster"), resMan->GetResource("ExplosionMaterial"), resMan->GetResource("FireTexture"), 1.0f);
	p->SetBlending(true);
	//p->SetScale(glm::vec3(10, 10, 10));
	p->SetPosition(position + glm::vec3(0, 2, 0) * orientation);
	return p;
}

} // namespace game
