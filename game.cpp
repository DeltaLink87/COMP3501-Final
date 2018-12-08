#include <iostream>
#include <time.h>
#include <sstream>

#include "game.h"
#include "bin/path_config.h"

namespace game {

// Some configuration constants
// They are written here as global variables, but ideally they should be loaded from a configuration file

// Main window settings
const std::string window_title_g = "Demo";
const unsigned int window_width_g = 800;
const unsigned int window_height_g = 600;
const bool window_full_screen_g = false;

// Viewport and camera settings
float camera_near_clip_distance_g = 0.01;
float camera_far_clip_distance_g = 1000.0;
float camera_fov_g = 20.0; // Field-of-view of camera
const glm::vec3 viewport_background_color_g(0.0, 0.0, 0.1);
glm::vec3 camera_position_g(0.0, 0.0, 800.0);
glm::vec3 camera_look_at_g(0.0, 0.0, 0.0);
glm::vec3 camera_up_g(0.0, 1.0, 0.0);

// Materials 1
const std::string material_directory_g = MATERIAL_DIRECTORY;


Game::Game(void){

    // Don't do work in the constructor, leave it for the Init() function
}


void Game::Init(void){

    // Run all initialization steps
    InitWindow();
    InitView();
    InitEventHandlers();

    // Set variables
    animating_ = true;

	thirdPerson_ = true;
}

       
void Game::InitWindow(void){

    // Initialize the window management library (GLFW)
    if (!glfwInit()){
        throw(GameException(std::string("Could not initialize the GLFW library")));
    }

    // Create a window and its OpenGL context
    if (window_full_screen_g){
        window_ = glfwCreateWindow(window_width_g, window_height_g, window_title_g.c_str(), glfwGetPrimaryMonitor(), NULL);
    } else {
        window_ = glfwCreateWindow(window_width_g, window_height_g, window_title_g.c_str(), NULL, NULL);
    }
    if (!window_){
        glfwTerminate();
        throw(GameException(std::string("Could not create window")));
    }

    // Make the window's context the current one
    glfwMakeContextCurrent(window_);

    // Initialize the GLEW library to access OpenGL extensions
    // Need to do it after initializing an OpenGL context
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK){
        throw(GameException(std::string("Could not initialize the GLEW library: ")+std::string((const char *) glewGetErrorString(err))));
    }
}


void Game::InitView(void){

    // Set up z-buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Set viewport
    int width, height;
    glfwGetFramebufferSize(window_, &width, &height);
    glViewport(0, 0, width, height);

    // Set up camera
    // Set current view
    camera_.SetView(camera_position_g, camera_look_at_g, camera_up_g);
    // Set projection
    camera_.SetProjection(camera_fov_g, camera_near_clip_distance_g, camera_far_clip_distance_g, width, height);
}


void Game::InitEventHandlers(void){

    // Set event callbacks
    glfwSetKeyCallback(window_, KeyCallback);
	glfwSetCursorPosCallback(window_, MouseCallback);
	glfwSetMouseButtonCallback(window_, MouseButtonCallback);
	glfwSetCursorEnterCallback(window_, MouseEnterCallback);
    glfwSetFramebufferSizeCallback(window_, ResizeCallback);

    // Set pointer to game object, so that callbacks can access it
    glfwSetWindowUserPointer(window_, (void *) this);
}


void Game::SetupResources(void){

    // Create a simple sphere to represent the asteroids
    resman_.CreateSphere("SimpleSphereMesh", 1.0, 10, 10);

    // Load material to be applied to asteroids
    std::string filename = std::string(MATERIAL_DIRECTORY) + std::string("/material");
    resman_.LoadResource(Material, "ObjectMaterial", filename.c_str());

	// Load material to be applied to skybox
	filename = std::string(MATERIAL_DIRECTORY) + std::string("/skybox");
	resman_.LoadResource(Material, "SkyboxMaterial", filename.c_str());


	//Load texture

	filename = std::string(TEXTURE_DIRECTORY) + std::string("/metal.png");
	resman_.LoadResource(Texture, "MetalTexture", filename.c_str());

	filename = std::string(TEXTURE_DIRECTORY) + std::string("/EnemyTex.jpg");
	resman_.LoadResource(Texture, "enemyTex", filename.c_str());

	filename = std::string(TEXTURE_DIRECTORY) + std::string("/torpedoTex.png");
	resman_.LoadResource(Texture, "TorpedoTex", filename.c_str());



	filename = std::string(TEXTURE_DIRECTORY) + std::string("/rustyMetal.jpg");
	resman_.LoadResource(Texture, "RustyMetal", filename.c_str());


	filename = std::string(TEXTURE_DIRECTORY) + std::string("/glassTex.jpg");
	resman_.LoadResource(Texture, "SubTex", filename.c_str());

	filename = std::string(TEXTURE_DIRECTORY) + std::string("/Sand.jpg");
	resman_.LoadResource(Texture, "sand", filename.c_str());

	filename = std::string(TEXTURE_DIRECTORY) + std::string("/stone.jpg");
	resman_.LoadResource(Texture, "stone", filename.c_str());


	filename = std::string(TEXTURE_DIRECTORY) + std::string("/dice.png");
	resman_.LoadResource(Texture, "DiceTexture", filename.c_str());


	filename = std::string(TEXTURE_DIRECTORY) + std::string("/fire.png");
	resman_.LoadResource(Texture, "FireTexture", filename.c_str());

	filename = std::string(TEXTURE_DIRECTORY) + std::string("/bubble.png");
	resman_.LoadResource(Texture, "BubbleTexture", filename.c_str());

	// Load cube map to be applied to skybox
	filename = std::string(MATERIAL_DIRECTORY) + std::string("/island/island.tga");
	resman_.LoadResource(CubeMap, "LakeCubeMap", filename.c_str());

	filename = std::string(MATERIAL_DIRECTORY) + std::string("/cube.obj");
	resman_.LoadResource(Mesh, "CubeMesh", filename.c_str());

	filename = std::string(MATERIAL_DIRECTORY) + std::string("/mine.obj");
	resman_.LoadResource(Mesh, "MineMesh", filename.c_str());

	filename = std::string(MATERIAL_DIRECTORY) + std::string("/Submarine.obj");
	resman_.LoadResource(Mesh, "SubMesh", filename.c_str());

	filename = std::string(MATERIAL_DIRECTORY) + std::string("/Enemy.obj");
	resman_.LoadResource(Mesh, "EnemySubMesh", filename.c_str());

	filename = std::string(MATERIAL_DIRECTORY) + std::string("/torpedo.obj");
	resman_.LoadResource(Mesh, "TorpedoMesh", filename.c_str());

	filename = std::string(MATERIAL_DIRECTORY) + std::string("/proppellor.obj");
	resman_.LoadResource(Mesh, "PropellerMesh", filename.c_str());


	filename = std::string(MATERIAL_DIRECTORY) + std::string("/Enemy.obj");
	resman_.LoadResource(Mesh, "enemyMesh", filename.c_str());

	filename = std::string(MATERIAL_DIRECTORY) + std::string("/UI");
	resman_.LoadResource(Material, "UI", filename.c_str());

	filename = std::string(MATERIAL_DIRECTORY) + std::string("/particle");
	resman_.LoadResource(Material, "ParticleMaterial", filename.c_str());

	filename = std::string(MATERIAL_DIRECTORY) + std::string("/explosion");
	resman_.LoadResource(Material, "ExplosionMaterial", filename.c_str());

	filename = std::string(MATERIAL_DIRECTORY) + std::string("/bubbles");
	resman_.LoadResource(Material, "BubblesMaterial", filename.c_str());


	// Create a simple sphere to represent the asteroids
	resman_.CreateCube("TurTowerCube");
	resman_.CreateCylinder("TurBodyCylinder", 1, 0.8);
	resman_.CreateCylinder("TurLowerCylinder", 1, 0.1);
	resman_.CreateCylinder("TurUpperCylinder", 1, 0.05);

	resman_.CreateCube("WorldCube", glm::vec3(0.6, 0.6, 0.45));

	resman_.CreateCylinder("PlayerCylinder", 2, 0.5);

	resman_.CreateCylinder("MissileCylinder", 1, 0.25);

	resman_.CreateSkybox("SkyboxMesh");

	resman_.CreateSphereParticles("SphereParticles");

	resman_.CreateParticleCluster("ParticleCluster");

	resman_.CreateParticleCluster("BubbleCluster", 50);

	// Load material to be applied to skybox
    filename = std::string(MATERIAL_DIRECTORY) + std::string("/skybox");
    resman_.LoadResource(Material, "SkyboxMaterial", filename.c_str());


	scene_.SetupDrawToTexture();

}


void Game::SetupScene(void){

    // Set background color for the scene
    scene_.SetBackgroundColor(viewport_background_color_g);

	world = new World("World", resman_.GetResource("WorldCube"), resman_.GetResource("ObjectMaterial"), resman_.GetResource("sand"));
	world->SetPosition(glm::vec3((world->getBounds()[0] + world->getBounds()[1]) / 2, world->getFloor() - 1.0, (world->getBounds()[4] + world->getBounds()[5]) / 2));
	world->SetScale(glm::vec3(world->getBounds()[1] - world->getBounds()[0], 2, world->getBounds()[5] - world->getBounds()[4]));
	scene_.AddNode(world);

	player_ = new Player("Player", &resman_);
	player_->SetPosition(glm::vec3(0, 100, 0));
	player_->SetReflectivity(0.2f);
	scene_.AddNode(player_);

	//We need to set up the number of lights uniform to initially zero.

	std::string numLightsName = "numLights";
	GLint numLightsIndex = glGetUniformLocation(resman_.GetResource("ObjectMaterial")->GetResource(), numLightsName.c_str());
	glUniform1i(numLightsIndex, 0);

	mainLight_ = new Light("main light", resman_.GetResource("PlayerCylinder"), resman_.GetResource("ObjectMaterial"));
	mainLight_->SetPosition(glm::vec3(0, 100, 150));
	mainLight_->SetSpecularColor(glm::vec3(1.0f, 1.0f, 0.5f));
	mainLight_->SetRange(200.00);

	skybox_ = new Skybox("Skybox", resman_.GetResource("SkyboxMesh"), resman_.GetResource("SkyboxMaterial"), resman_.GetResource("LakeCubeMap"), &camera_);
	scene_.AddNode(skybox_);

    // Create asteroid field
    //CreateAsteroidField();
	CreateMineField(100);
	CreateSubmarines(50);
	CreateTowers(10);
}


void Game::MainLoop(void){
	int direction = 1;
    // Loop while the user did not close the window
    while (!glfwWindowShouldClose(window_)){
        // Animate the scene
        if (animating_){
            static double last_time = 0;
            double current_time = glfwGetTime();
            if ((current_time - last_time) > 0.05){
                scene_.Update();
                last_time = current_time;
            }
        }

		//death checking 
		if (player_->isDead()) {
			scene_.RemoveNode(player_);
			//return;
		}
		else {
			Attack* newAttack = player_->getNewAttack();
			if (newAttack) {
				attacks_.push_back(newAttack);
				SceneNode* newNode = newAttack->createSceneNode(&resman_);
				scene_.AddNode(newNode);
			}
		}

		for (int i = 0; i < enemies_.size(); i++) {
			Attack* newAttack = enemies_[i]->getNewAttack();
			if (newAttack) {
				attacks_.push_back(newAttack);
				SceneNode* newNode = newAttack->createSceneNode(&resman_);
				scene_.AddNode(newNode);
			}

			if (enemies_[i]->isDead()) {
				Enemy* rmEnemy = enemies_[i];
				player_->GainPoint();
				enemies_.erase(enemies_.begin() + i);
				scene_.RemoveNode(rmEnemy);
				i--;
			}
		}

		for (int i = 0; i < attacks_.size(); i++) {
			attacks_[i]->Update();

			if (!player_->isDead() && attacks_[i]->getBounds().intersects(player_->getBounds())) {
				Attack* rmAttack = attacks_[i];
				attacks_.erase(attacks_.begin() + i);
				scene_.RemoveNode(rmAttack->getSceneNode());
				player_->takeDamage(1);

				SceneNode* particles = rmAttack->hitParticles(&resman_);
				if (particles)
					scene_.AddNode(particles);

				i--;
				delete rmAttack;
				continue;
			}


			for (int j = 0; j < enemies_.size(); j++) {
				if (attacks_[i]->getBounds().intersects(enemies_[j]->getBounds())) {
					Attack* rmAttack = attacks_[i];
					attacks_.erase(attacks_.begin() + i);

					enemies_[j]->takeDamage(1);
					scene_.RemoveNode(rmAttack->getSceneNode());

					SceneNode* particles = rmAttack->hitParticles(&resman_);
					if (particles) 
						scene_.AddNode(particles);

					i--;
					delete rmAttack;

					break;
				}
			}
		}

		//Bounding the Player within the game world
		if (player_->GetPosition().x < world->getBounds()[0])
			player_->Translate(glm::vec3(world->getBounds()[0] - player_->GetPosition().x, 0, 0));
		else if (player_->GetPosition().x > world->getBounds()[1])
			player_->Translate(glm::vec3(world->getBounds()[1] - player_->GetPosition().x, 0, 0));
		if (player_->GetPosition().y < world->getBounds()[2])
			player_->Translate(glm::vec3(0, world->getBounds()[2] - player_->GetPosition().y, 0));
		else if (player_->GetPosition().y > world->getBounds()[3])
			player_->Translate(glm::vec3(0, world->getBounds()[3] - player_->GetPosition().y, 0));
		if (player_->GetPosition().z < world->getBounds()[4])
			player_->Translate(glm::vec3(0, 0, world->getBounds()[4] - player_->GetPosition().z));
		else if (player_->GetPosition().z > world->getBounds()[5])
			player_->Translate(glm::vec3(0, 0, world->getBounds()[5] - player_->GetPosition().z));




		/*if (firingLaser_) {
			std::vector<int> astHitIdx;
			glm::vec3 beamPos1 = player_->GetPosition();
			glm::vec3 beamPos2 = player_->GetPosition() + glm::vec3(0, 0, 50) * player_->GetForward();
			for (int i = 0; i < asteriods_.size(); i++) {
				float dis = glm::length(glm::cross(beamPos2 - beamPos1, beamPos1 - asteriods_[i]->GetPosition())) / glm::length(beamPos2 - beamPos1);
				if (dis < 1.25) {
					scene_.RemoveNode(asteriods_[i]);
					astHitIdx.push_back(i);
				}
			}
		}

		/*std::cout << (player_->GetForward() * 50.0f).x << ", " << (player_->GetForward() * 50.0f).y << ", " << (player_->GetForward() * 50.0f).z << std::endl;
		glm::vec3 lookAt = player_->GetPosition() + player_->GetForward() * 50.0f;
		glm::vec3 upVec(0, 1, 0);
		if (thirdPerson_)
			camera_.SetView(player_->GetPosition() + -30.0f * player_->GetForward() + glm::vec3(0, 5, 0), lookAt, upVec);
		else camera_.SetView(player_->GetPosition() + player_->GetForward() * 2.0f, lookAt, upVec);*/

		glm::vec3 upVec(0, 1, 0);
		if (thirdPerson_) {
			glm::vec3 lookAt = player_->GetPosition() + glm::vec3(0, 0, 50) * camRotation_ * player_->GetForward();
			camera_.SetView(player_->GetPosition() + glm::vec3(0, 5, -30) * camRotation_ * player_->GetForward(), lookAt, upVec);
		}
		else {
			glm::vec3 lookAt = player_->GetPosition() + glm::vec3(0, 0, 50) * player_->GetForward();
			camera_.SetView(player_->GetPosition() + (glm::vec3(0, 0, 7.8) * player_->GetScale()) * player_->GetForward(), lookAt, upVec);
		}

		//mainLight_->SetPosition(mainLight_->GetPosition() + glm::vec3(glm::sin(glfwGetTime()), cos(glfwGetTime()), 0.0f));
		//mainLight_->SetPosition(mainLight_->GetPosition() + glm::vec3(0.0, 50.0, 0.0));
		if (mainLight_->GetRange() > 300) {
			direction = -1;
		}
		else if (mainLight_->GetRange() < 100) {
			direction = 1;
		}
		mainLight_->SetRange(mainLight_->GetRange() + (10 * direction));
		//skybox_->SetPosition(camera_.GetPosition());

		skybox_->SetPosition(camera_.GetPosition());
        // Draw the scene
        //scene_.Draw(&camera_);
		scene_.DrawToTexture(&camera_);


		scene_.DisplayTexture(resman_.GetResource("UI")->GetResource());

        // Push buffer drawn in the background onto the display
        glfwSwapBuffers(window_);

        // Update other events like input handling
        glfwPollEvents();
    }
}


void Game::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){

    // Get user data with a pointer to the game class
    void* ptr = glfwGetWindowUserPointer(window);
    Game *game = (Game *) ptr;

    // Quit game if 'esc' is pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }

    // Stop animation if 'p' is pressed
    if (key == GLFW_KEY_P && action == GLFW_PRESS){
        game->animating_ = (game->animating_ == true) ? false : true;
    }

	if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		game->thirdPerson_ = !game->thirdPerson_;
	}

    if (key == GLFW_KEY_W){
		game->player_->Accelerate();
    }
    if (key == GLFW_KEY_S){
		game->player_->Deccelerate();
    }
    if (key == GLFW_KEY_A){
		game->player_->RotateLeft();
    }
    if (key == GLFW_KEY_D){
		game->player_->RotateRight();
    }
    if (key == GLFW_KEY_LEFT_SHIFT){
		game->player_->Rise();
    }
    if (key == GLFW_KEY_LEFT_CONTROL/* && action == GLFW_PRESS*/){
		game->player_->Fall();
		//ParticleFountain * bubbles = (ParticleFountain *)game->scene_.GetNode("Bubbles");
		//bubbles->StopFountain();
    }
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		game->player_->fire();
	}
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		game->player_->changeFireType(1);
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		game->player_->changeFireType(2);
	}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		game->player_->changeFireType(3);
	}
}

void Game::MouseCallback(GLFWwindow* window, double x, double y) {
	// Get user data with a pointer to the game class
	void* ptr = glfwGetWindowUserPointer(window);
	Game *game = (Game *)ptr;

	if (game->prevMouseX != -999 && game->prevMouseY != -999 && game->rotateCam) {
		float horzRotation = ((game->prevMouseX - x) / 200.0) / glm::pi<float>();
		float vertRotation = ((game->prevMouseY - y) / 200.0) / glm::pi<float>();
		game->camRotation_ *= glm::angleAxis(horzRotation, game->camRotation_ * glm::vec3(0.0, 1.0, 0.0));
		game->camRotation_ *= glm::angleAxis(vertRotation, game->camRotation_ * glm::vec3(1.0, 0.0, 0.0));
	}

	game->prevMouseX = x;
	game->prevMouseY = y;
}

void Game::MouseButtonCallback(GLFWwindow* window, int button, int action, int mod) {
	// Get user data with a pointer to the game class
	void* ptr = glfwGetWindowUserPointer(window);
	Game *game = (Game *)ptr;

	if (button == 0 && action == GLFW_PRESS)
		game->rotateCam = true;
	if (button == 0 && action == GLFW_RELEASE)
		game->rotateCam = false;

	if (button == 1 && action == GLFW_PRESS)
		game->camRotation_ = glm::angleAxis(0.0f, glm::vec3(1.0, 0.0, 0.0));
}

void Game::MouseEnterCallback(GLFWwindow* window, int entered) {
	// Get user data with a pointer to the game class
	void* ptr = glfwGetWindowUserPointer(window);
	Game *game = (Game *)ptr;

	if (!entered) {
		game->prevMouseX = -999;
		game->prevMouseY = -999;
	}
}


void Game::ResizeCallback(GLFWwindow* window, int width, int height){

    // Set up viewport and camera projection based on new window size
    glViewport(0, 0, width, height);
    void* ptr = glfwGetWindowUserPointer(window);
    Game *game = (Game *) ptr;
    game->camera_.SetProjection(camera_fov_g, camera_near_clip_distance_g, camera_far_clip_distance_g, width, height);
}


Game::~Game(){
    
    glfwTerminate();
}


Asteroid *Game::CreateAsteroidInstance(std::string entity_name, std::string object_name, std::string material_name, std::string texture_name){

    // Get resources
    Resource *geom = resman_.GetResource(object_name);
    if (!geom){
        throw(GameException(std::string("Could not find resource \"")+object_name+std::string("\"")));
    }

    Resource *mat = resman_.GetResource(material_name);
    if (!mat){
        throw(GameException(std::string("Could not find resource \"")+material_name+std::string("\"")));
    }



	Resource *tex = resman_.GetResource(texture_name);
	if (!mat) {
		throw(GameException(std::string("Could not find resource \"") + texture_name + std::string("\"")));
	}

    // Create asteroid instance
    Asteroid *ast = new Asteroid(entity_name, geom, mat,tex);
    scene_.AddNode(ast);
    return ast;
}


void Game::CreateAsteroidField(int num_asteroids){

    // Create a number of asteroid instances
    for (int i = 0; i < num_asteroids; i++){
        // Create instance name
        std::stringstream ss;
        ss << i;
        std::string index = ss.str();
        std::string name = "AsteroidInstance" + index;

        // Create asteroid instance
        Asteroid *ast = CreateAsteroidInstance(name, "MineMesh", "ObjectMaterial", "RustyMetal");
		asteriods_.push_back(ast);

        // Set attributes of asteroid: random position, orientation, and
        // angular momentum
		ast->SetScale(glm::vec3(3,3,3));
        ast->SetPosition(world->getRandomPosition());
        ast->SetOrientation(glm::normalize(glm::angleAxis(glm::pi<float>()*((float) rand() / RAND_MAX), glm::vec3(((float) rand() / RAND_MAX), ((float) rand() / RAND_MAX), ((float) rand() / RAND_MAX)))));
        ast->SetAngM(glm::normalize(glm::angleAxis(0.05f*glm::pi<float>()*((float) rand() / RAND_MAX), glm::vec3(((float) rand() / RAND_MAX), ((float) rand() / RAND_MAX), ((float) rand() / RAND_MAX)))));
    }
}

void Game::CreateMineField(int num_mines) {

	// Create a number of asteroid instances
	for (int i = 0; i < num_mines; i++) {
		// Create instance name
		std::stringstream ss;
		ss << i;
		std::string index = ss.str();
		std::string name = "MineInstance" + index;

		// Create asteroid instance
		Mine *mine = new Mine(name, &resman_);
		enemies_.push_back(mine);
		scene_.AddNode(mine);

		// Set attributes of asteroid: random position, orientation, and
		mine->setPlayer(player_);
		mine->SetPosition(world->getRandomPosition());
		mine->SetOrientation(glm::normalize(glm::angleAxis(glm::pi<float>()*((float)rand() / RAND_MAX), glm::vec3(((float)rand() / RAND_MAX), ((float)rand() / RAND_MAX), ((float)rand() / RAND_MAX)))));
	}
}

void Game::CreateSubmarines(int num_subs) {

	// Create a number of asteroid instances
	for (int i = 0; i < num_subs; i++) {
		// Create instance name
		std::stringstream ss;
		ss << i;
		std::string index = ss.str();
		std::string name = "SubInstance" + index;

		// Create asteroid instance
		Submarine *sub = new Submarine(name, &resman_);
		enemies_.push_back(sub);
		scene_.AddNode(sub);

		// Set attributes of asteroid: random position, orientation, and
		sub->setPlayer(player_);
		sub->SetPosition(world->getRandomPosition());
		sub->Rotate(glm::normalize(glm::angleAxis(glm::pi<float>()*((float)rand() / RAND_MAX), glm::vec3(0.0, 1.0, 0.0))));
	}
}

void Game::CreateTowers(int num_towers) {
	for (int i = 0; i < num_towers; i++) {
		// Create instance name
		std::stringstream ss;
		ss << i;
		std::string index = ss.str();
		std::string name = "TurretInstance" + index;

		Turret *tower = new Turret(name, &resman_);
		tower->SetScale(glm::vec3(5, 5, 5));
		tower->setPlayer(player_);
		tower->SetPosition(world->getRandomFloorPosition() + glm::vec3(0, 2, 0));
		scene_.AddNode(tower);
		enemies_.push_back(tower);

	}
}

} // namespace game
