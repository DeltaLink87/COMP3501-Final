#ifndef ENEMY_H_
#define ENEMY_H_

#include "resource.h"
#include "scene_node.h"
#include "player.h"
#include "bound.h"

namespace game {
	class Enemy : public SceneNode
	{
	public:
		Enemy(const std::string name, const Resource *geometry, const Resource *material, const Resource *texture = NULL);
		~Enemy();

		virtual void Update(void);
		void takeDamage(int damage);
		bool isDead();

		void setPlayer(Player* player);

		Bound getBounds() const;
		Attack* getNewAttack();


	protected:
		Player* player = NULL;

		Bound bounds = Bound(glm::vec3(), glm::vec3(), 1);

		Attack* attack = NULL;

		int health = 10;

	};
}

#endif // TURRET_H_


