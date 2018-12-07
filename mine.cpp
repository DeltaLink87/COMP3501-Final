#include "mine.h"
#include <math.h>
#include <iostream>

namespace game {

Mine::Mine(const std::string name, ResourceManager* rm) : Enemy(name + "Mine", rm->GetResource("MineMesh"), rm->GetResource("ObjectMaterial"), rm->GetResource("RustyMetal")) {
	health = 1;
	bobblingTimer = (float)rand() / RAND_MAX * glm::pi<float>();
	SetScale(glm::vec3(0.5, 0.5, 0.5));
	bounds = Bound(glm::vec3(), glm::vec3(), 3.0f * 0.5f);
}

Mine::~Mine() {}


void Mine::Update() {
	bobblingTimer += 0.1;
	bobblingTimer = fmod(bobblingTimer, glm::pi<float>() * 2);
	this->Translate(glm::vec3(0.0, 0.1 * sin(bobblingTimer), 0.0));

	bounds.setPositions(GetPosition() + glm::vec3(0, 0.05, 0), GetPosition() + glm::vec3(0, -0.05, 0));
	if (player) {
		if (player->getBounds().intersects(bounds)) {
			attack = new MineAttack("MineExplosion", GetPosition());
			attack->SetDamage(4);
			health = 0;
		}
	}
}

MineAttack::MineAttack(const std::string name, glm::vec3 pos) : Attack(name, "SimpleSphereMesh", "ObjectMaterial", "FireTexture") {
	this->SetPosition(pos);
	bounds = Bound(position + glm::vec3(0, -0.0001, 0), position + glm::vec3(0, 0.0001, 0), 2);
}

MineAttack::~MineAttack() {}

void MineAttack::UpdateBounds() {
	bounds.setPositions(position + glm::vec3(0, -0.0001, 0), position + glm::vec3(0, 0.0001, 0));
}

ParticleSystem* MineAttack::hitParticles(ResourceManager* resMan) {
	ParticleSystem* p = new ParticleSystem(name + "Explosion", resMan->GetResource("BubbleCluster"), resMan->GetResource("ExplosionMaterial"), resMan->GetResource("FireTexture"), 1.0f);
	p->SetBlending(true);
	//p->SetScale(glm::vec3(10, 10, 10));
	p->SetPosition(position + glm::vec3(0, 2, 0) * orientation);
	return p;
}

}

