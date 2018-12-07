#include "particle_system.h"

game::ParticleSystem::ParticleSystem(const std::string name, const Resource * geometry, const Resource * material, const Resource * texture, float lifespan) : SceneNode(name, geometry, material, texture), lifespan_(lifespan){
	creationTime_ = glfwGetTime();
}

void game::ParticleSystem::Update(void)
{
	if (glfwGetTime() - creationTime_ > lifespan_) {
		pleaseKill_ = true;
	}
}

void game::ParticleSystem::SetupShader(GLuint program)
{
	SceneNode::SetupShader(program);

	//Provides a value between 0 and 1 depending on how long it's been since the system was created, and how long the lifespan is.
	GLint progress_var = glGetUniformLocation(program, "progress");
	double current_time = glfwGetTime();
	float progress = (current_time - creationTime_) / lifespan_;
	glUniform1f(progress_var, progress);
}
