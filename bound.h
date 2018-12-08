#ifndef BOUND_H_
#define BOUND_H_

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

namespace game {

    // Abstraction of an asteroid
    class Bound {

        public:
            // Create asteroid from given resources
			Bound(glm::vec3 p1, glm::vec3 p2, float radius);

            // Destructor
            ~Bound();
            
			void setPositions(glm::vec3 p1, glm::vec3 p2);
			void setRadius(float bound);
			float GetRadius();

			glm::vec3 GetPoint1() const;
			glm::vec3 GetPoint2() const;

			double distanceBetween(const Bound other);
			bool intersects(const Bound other);

            
        private:
			glm::vec3 p1;
			glm::vec3 p2;
			float radius;

    }; // class Asteroid

} // namespace game

#endif // ASTEROID_H_
