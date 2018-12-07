#include "mine.h"
#include <math.h>
#include <iostream>

namespace game {

Mine::Mine(const std::string name, ResourceManager* rm) : Enemy(name + "Mine", rm->GetResource("MineMesh"), rm->GetResource("ObjectMaterial"), rm->GetResource("MetalTexture")) {
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
			attack = new Attack("MineExplosion", "SimpleSphereMesh", "ObjectMaterial");
			attack->SetPosition(GetPosition());
			attack->SetDamage(4);
			health = 0;
		}
	}
}

}

