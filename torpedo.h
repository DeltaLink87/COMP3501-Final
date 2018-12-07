#ifndef TORPEDO_H_
#define TORPEDO_H_

#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>

#include "resource.h"
#include "scene_node.h"
#include "resource_manager.h"
#include "bound.h"
#include "attack.h"

namespace game {

    // Abstraction of an asteroid
    class Torpedo : public Attack {

        public:
            // Create asteroid from given resources
			Torpedo(const std::string name, glm::vec3 pos, glm::vec3 movement, glm::quat orientation);

            // Destructor
            ~Torpedo();

			void UpdateBounds();
            
			ParticleSystem* hitParticles(ResourceManager* resMan);
    }; // class Asteroid

} // namespace game

#endif // ASTEROID_H_
