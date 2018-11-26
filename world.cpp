#include "world.h"

namespace game {

World::World(const std::string name, const Resource *geometry, const Resource *material) : SceneNode(name, geometry, material) {
	SetPosition(glm::vec3((getBounds()[0] + getBounds()[1]) / 2, getFloor() - 1.0, (getBounds()[4] + getBounds()[5]) / 2));
	SetScale(glm::vec3(getBounds()[1] - getBounds()[0], 2, getBounds()[5] - getBounds()[4]));
}


World::~World(){
}


void World::Update(void){

    Rotate(angm_);
}

float World::getFloor() {
	return worldBounds[2];
}

float World::getCeil() {
	return worldBounds[3];
}

float* World::getBounds() {
	return worldBounds;
}

glm::vec3 World::getRandomPosition() {
	return glm::vec3(worldBounds[0] + (worldBounds[1] - worldBounds[0])*((float)rand() / RAND_MAX), 
		worldBounds[2] + (worldBounds[3] - worldBounds[2])*((float)rand() / RAND_MAX), 
		worldBounds[4] + (worldBounds[5] - worldBounds[4])*((float)rand() / RAND_MAX));
}

glm::vec3 World::getRandomFloorPosition() {
	return glm::vec3(worldBounds[0] + (worldBounds[1] - worldBounds[0])*((float)rand() / RAND_MAX),
		getFloor(),
		worldBounds[4] + (worldBounds[5] - worldBounds[4])*((float)rand() / RAND_MAX));
}
            
} // namespace game
