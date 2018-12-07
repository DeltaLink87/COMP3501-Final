#include "particle_fountain.h"

game::ParticleFountain::ParticleFountain(const std::string name, const Resource * geometry, const Resource * material, const Resource * texture, float lifespan) :
	ParticleSystem(name, geometry, material, texture, lifespan), 
	phase(1),
	stopped_(false)
{
}

void game::ParticleFountain::StopFountain()
{
	stopped_ = true;
}

void game::ParticleFountain::Update(void)
{
	ParticleSystem::Update();
	double current_time = glfwGetTime();
	float progress = (current_time - creationTime_) / lifespan_;

	if (phase < 3) {
		pleaseKill_ = false;
	}

	if (glfwGetTime() - creationTime_ > lifespan_) {
		if (phase == 1) {
			phase++;
		}

		if (phase < 3) {
			creationTime_ += lifespan_;
		}
		
		if (stopped_) {
			phase = 3;
		}
	}
}

void game::ParticleFountain::SetupShader(GLuint program)
{
	ParticleSystem::SetupShader(program);

	GLint phase_var = glGetUniformLocation(program, "phase");
	glUniform1i(phase_var, phase);
}
