#ifndef ATTACK_H_
#define ATTACK_H_

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
#include "particle_system.h"
#include "bound.h"

namespace game {

    // Abstraction of an asteroid
    class Attack {

        public:
            // Create asteroid from given resources
			Attack(const std::string name, const std::string geoyName, const std::string matName, const std::string texName = "");

            // Destructor
            ~Attack();
            

            // Update geometry configuration
            void Update(void);
			virtual void UpdateBounds();

			virtual SceneNode* createSceneNode(ResourceManager* resMan);
			SceneNode* getSceneNode();

			virtual ParticleSystem* hitParticles(ResourceManager* resMan);

			void SetPosition(glm::vec3 position);
			void SetOrientation(glm::quat orientation);
			void SetMovment(glm::vec3 move);
			void SetAcceleration(glm::vec3 acc);

			void SetDamage(int dmg);
			int GetDamage();

			glm::quat GetOrientation() const;

			Bound getBounds() const;
        protected:
            // Angular momentum of asteroid
			std::string name;
			std::string geoName;
			std::string matName;
			std::string texName;
			SceneNode* node = NULL;

			Bound bounds = Bound(glm::vec3(), glm::vec3(), 1);

			glm::vec3 position = glm::vec3(0, 0, 0);
			glm::quat orientation = glm::angleAxis(glm::pi<float>() * 0, glm::vec3(1.0, 0.0, 0.0));
			glm::vec3 movement = glm::vec3(0, 0, 0);
			glm::vec3 accelaration = glm::vec3(0, 0, 0);

			int damage = 1;

    }; // class Asteroid

} // namespace game

#endif // ASTEROID_H_
