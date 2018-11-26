#include "Attack.h"

namespace game {

Attack::Attack(const std::string name, const std::string geoName, const std::string matName) {
	this->name = name;
	this->geoName = geoName;
	this->matName = matName;
}


Attack::~Attack(){
	if (node != NULL)
		delete node;
}


void Attack::Update() {
	movement += accelaration;
	position += movement;

	if (node != NULL) {
		node->SetPosition(position);
		node->SetOrientation(orientation);
	}
	bounds.setPositions(position + glm::vec3(0, 0.5, 0) * orientation, position + glm::vec3(0, -0.5, 0) * orientation);
}

SceneNode* Attack::createSceneNode(ResourceManager* resMan) {
	if (node != NULL)
		delete node;

	node = new SceneNode(name, resMan->GetResource(geoName), resMan->GetResource(matName));
	node->SetPosition(position);
	node->SetOrientation(orientation);

	return node;
}

SceneNode* Attack::getSceneNode() {
	return node;
}

void Attack::SetPosition(glm::vec3 position) {
	this->position = position;
}

void Attack::SetOrientation(glm::quat orientation) {
	this->orientation = orientation;
}

void Attack::SetMovment(glm::vec3 move) {
	this->movement = move;
}

void Attack::SetAcceleration(glm::vec3 acc) {
	this->accelaration = acc;
}

glm::quat Attack::GetOrientation() const {
	return orientation;
}

Bound Attack::getBounds() const {
	return bounds;
}
            
} // namespace game
