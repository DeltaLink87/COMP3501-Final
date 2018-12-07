#include "skybox.h"

game::Skybox::Skybox(const std::string name, const Resource * geometry, const Resource * material, const Resource * texture, Camera * camera): SceneNode(name, geometry, material, texture), camera_(camera)
{
	SetScale(glm::vec3(50.0, 50.0, 50.0));
}

void game::Skybox::Update(void)
{
	//SetPosition(camera_->GetPosition());
}
