#include "Attack.h"

namespace game {

Attack::Attack(const std::string name, const std::string geoName, const std::string matName, const std::string texName) {
	this->name = name;
	this->geoName = geoName;
	this->matName = matName;
	this->texName = texName;
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
	UpdateBounds();
}

void Attack::UpdateBounds() {
	bounds.setPositions(position + glm::vec3(0, 1, 0) * orientation, position + glm::vec3(0, -1, 0) * orientation);
}

SceneNode* Attack::createSceneNode(ResourceManager* resMan) {
	if (node != NULL)
		delete node;

	if (texName.compare("") == 0)
		node = new SceneNode(name, resMan->GetResource(geoName), resMan->GetResource(matName));
	else 
		node = new SceneNode(name, resMan->GetResource(geoName), resMan->GetResource(matName), resMan->GetResource(texName));
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

void Attack::SetDamage(int dmg) {
	damage = dmg;
}

int Attack::GetDamage() {
	return damage;
}
            
} // namespace game
