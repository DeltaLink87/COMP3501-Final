#ifndef DEPTHCHARGE_H_
#define DEPTHCHARGE_H_

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
    class DepthCharge : public Attack {

        public:
            // Create asteroid from given resources
			DepthCharge(const std::string name, glm::vec3 pos, glm::quat orientation);

            // Destructor
            ~DepthCharge();

			void UpdateBounds();

			SceneNode* createSceneNode(ResourceManager* resMan);
            
			ParticleSystem* hitParticles(ResourceManager* resMan);

    }; // class Asteroid

} // namespace game

#endif // ASTEROID_H_
