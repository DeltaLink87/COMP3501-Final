#include "mine.h"
#include <math.h>
#include <iostream>

namespace game {

Mine::Mine(const std::string name, ResourceManager* rm) : Enemy(name + "Mine", rm->GetResource("SimpleSphereMesh"), rm->GetResource("ObjectMaterial")) {
	health = 1;
	bobblingTimer = (float)rand() / RAND_MAX * glm::pi<float>();
}

Mine::~Mine() {}


void Mine::Update() {
	bobblingTimer += 0.1;
	bobblingTimer = fmod(bobblingTimer, glm::pi<float>() * 2);
	this->Translate(glm::vec3(0.0, 0.1 * sin(bobblingTimer), 0.0));

	bounds = Bound(GetPosition() + glm::vec3(0, -0.01, 0) * GetScale(), GetPosition() + glm::vec3(0, 0.01, 0) * GetScale(), 2 * GetScale().x);
	if (player) {
		if (player->getBounds().intersects(bounds)) {
			attack = new Attack("MineExplosion", "SimpleSphereMesh", "ObjectMaterial");
			attack->SetPosition(GetPosition());
			health = 0;
		}
	}
}

}

