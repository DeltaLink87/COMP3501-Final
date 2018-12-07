#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "scene_node.h"

namespace game {
	class ParticleSystem : public SceneNode {
		public:
			ParticleSystem(const std::string name, const Resource *geometry, const Resource *material, const Resource *texture, float lifespan);
			virtual void Update(void);
		protected:
			float lifespan_;
			float creationTime_;
			virtual void SetupShader(GLuint program);
	};
}
#endif