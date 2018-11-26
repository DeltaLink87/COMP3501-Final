#ifndef GAME_H_
#define GAME_H_

#include <exception>
#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "scene_graph.h"
#include "resource_manager.h"
#include "camera.h"
#include "asteroid.h"
#include "turret.h"
#include "player.h"
#include "world.h"

#include <iostream>

namespace game {

    // Exception type for the game
    class GameException: public std::exception
    {
        private:
            std::string message_;
        public:
            GameException(std::string message) : message_(message) {};
            virtual const char* what() const throw() { return message_.c_str(); };
            virtual ~GameException() throw() {};
    };

    // Game application
    class Game {

        public:
            // Constructor and destructor
            Game(void);
            ~Game();
            // Call Init() before calling any other method
            void Init(void); 
            // Set up resources for the game
            void SetupResources(void);
            // Set up initial scene
            void SetupScene(void);
            // Run the game: keep the application active
            void MainLoop(void); 

        private:
            // GLFW window
            GLFWwindow* window_;

            // Scene graph containing all nodes to render
            SceneGraph scene_;

            // Resources available to the game
            ResourceManager resman_;

            // Camera abstraction
            Camera camera_;

			World* world;

			Player* player_;

            // Flag to turn animation on/off
            bool animating_;
			bool thirdPerson_ = true;

			double prevMouseY = -999, prevMouseX = -999;
			glm::quat camRotation_ = glm::angleAxis(0 / glm::pi<float>(), glm::vec3(0.0, 0.0, 1.0));

			std::vector<Attack *> attacks_;
			std::vector<Turret *> turrets_;
			std::vector<Asteroid *> asteriods_;

            // Methods to initialize the game
            void InitWindow(void);
            void InitView(void);
            void InitEventHandlers(void);
 
            // Methods to handle events
            static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void MouseCallback(GLFWwindow* window, double x, double y);
			static void MouseEnterCallback(GLFWwindow* window, int entered);
            static void ResizeCallback(GLFWwindow* window, int width, int height);

            // Asteroid field
            // Create instance of one asteroid
            Asteroid *CreateAsteroidInstance(std::string entity_name, std::string object_name, std::string material_name);
            // Create entire random asteroid field
            void CreateAsteroidField(int num_asteroids = 1500);
			// Create entire random towers
			void CreateTowers(int num_towers = 10);

    }; // class Game

} // namespace game

#endif // GAME_H_
