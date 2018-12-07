#ifndef PARTICLE_FOUNTAIN_H
#define PARTICLE_FOUNTAIN_H

#include "particle_system.h"

namespace game {
	class ParticleFountain : public ParticleSystem {
		public:
			ParticleFountain(const std::string name, const Resource *geometry, const Resource *material, const Resource *texture, float lifespan);
			void StopFountain();
			virtual void Update(void);
		protected:
			//Starts in phase 1 for initialization, goes to phase two for most of its life, phase three is winding down
			int phase;
			virtual void SetupShader(GLuint program);
			bool stopped_;
	};
}

#endif