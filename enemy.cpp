#include "enemy.h"
#include <math.h>
#include <iostream>

namespace game {

Enemy::Enemy(const std::string name, const Resource *geometry, const Resource *material, const Resource *texture, const Resource *envMap) : SceneNode(name, geometry, material, texture, envMap) {}

Enemy::~Enemy() {
	if (attack != NULL)
		delete attack;
}


void Enemy::Update() {}


void Enemy::takeDamage(int damage) {
	health -= damage;
	std::printf("This Enemies Health is: %d\n", health);
}

bool Enemy::isDead() {
	return health <= 0;
}

void Enemy::setPlayer(Player* player) {
	this->player = player;
}

Bound Enemy::getBounds() const {
	return bounds;
}

Attack* Enemy::getNewAttack() {
	Attack* usedAttack = this->attack;
	this->attack = NULL;
	return usedAttack;
}

}

