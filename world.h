#ifndef WORLD_H_
#define WORLD_H_

#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>

#include "resource.h"
#include "scene_node.h"

namespace game {

    // Abstraction of an asteroid
    class World : public SceneNode {

        public:
            // Create asteroid from given resources
			World(const std::string name, const Resource *geometry, const Resource *material);

            // Destructor
            ~World();

            // Update geometry configuration
            void Update(void);

			float getFloor();
			float getCeil();
			float* getBounds();

			glm::vec3 getRandomPosition();
			glm::vec3 getRandomFloorPosition();
            
        private:
            // Angular momentum of asteroid
            glm::quat angm_;

			float* worldBounds = new float[6]{-300.0, 300.0, 0.0, 600.0, -300.0, 300.0};
    }; // class Asteroid

} // namespace game

#endif // ASTEROID_H_
