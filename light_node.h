#ifndef LIGHT_NODE_H
#define LIGHT_NODE_H

#include "scene_node.h"

namespace game {
	class Light : public SceneNode
	{
	public:
		Light(const std::string name, const Resource * mesh, const Resource *material);
		~Light();

		std::string GetUniformName();
		float GetRange();
		glm::vec3 GetSpecularColor();

		void SetRange(float value);
		void SetSpecularColor(glm::vec3 value);
		void SetPosition(glm::vec3 value);
	private:
		std::string uniformName;
		//THe range indicates the distance from the light source at which the light provides full illumination; beyond that range, the light decreases until twice the range, at which point only ambient light is provided
		float range;
		//Ambient and diffuse light comes from the texture, but the specular color comes from the light
		glm::vec3 specularColor;
		//THese indexes indicate the number used to retrieve/change the position, range, and specular color values in the shader. The actual shader program is stored as the light node's Material.
		GLint positionIndex;
		GLint rangeIndex;
		GLint specColorIndex;
	};
}

#endif // PLAYER_H_