#ifndef MINE_H_
#define MINE_H_

#include "resource.h"
#include "enemy.h"
#include "resource_manager.h"
#include "player.h"
#include "bound.h"

namespace game {
	class Mine : public Enemy
	{
	public:
		Mine(const std::string name, ResourceManager* rm);
		~Mine();

		void Update(void);

	private:
		float bobblingTimer = 0;
	};
}

#endif // TURRET_H_


