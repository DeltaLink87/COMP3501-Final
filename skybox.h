#ifndef SKYBOX_H
#define SKYBOX_H

#include "scene_node.h"

namespace game {
	class Skybox : public SceneNode {
		public:
			Skybox(const std::string name, const Resource *geometry, const Resource *material, const Resource *texture, Camera * camera);
			virtual void Update(void);
		protected:
			Camera * camera_;
	};
}

#endif