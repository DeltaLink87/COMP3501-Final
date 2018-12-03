#include "light_node.h"

game::Light::Light(const std::string name, const Resource * mesh, const Resource *material) : SceneNode(name, mesh, material), range(1.0), specularColor(glm::vec3(1.0f))
{
	glUseProgram(material_);
	std::string numLightsName = "lightNum";
	GLint numLightsIndex = glGetUniformLocation(material->GetResource(), numLightsName.c_str());
	int numLights;
	glGetUniformiv(material->GetResource(), numLightsIndex, &numLights);
	numLights++;
	glUniform1i(numLightsIndex, numLights);

	uniformName = "light" + std::to_string(numLights);
	
	std::string specificUniformName;

	specificUniformName = uniformName + "Pos";
	//numLightsName = "light1Pos";
	//specificUniformName.append("Pos");
	positionIndex = glGetUniformLocation(material->GetResource(), specificUniformName.c_str());

	specificUniformName = uniformName + "Range";
	//numLightsName = "light1Range";
	//specificUniformName.append("Range");
	rangeIndex = glGetUniformLocation(material->GetResource(), specificUniformName.c_str());

	specificUniformName = uniformName + "Specular";
	//numLightsName = "light1Specular";
	//specificUniformName.append("Specular");
	specColorIndex = glGetUniformLocation(material->GetResource(), specificUniformName.c_str());

	//Default values
	SetRange(100.0);
	SetSpecularColor(glm::vec3(1.0, 1.0, 1.0));
	SetPosition(glm::vec3(0.0, 0.0, 0.0));
}

game::Light::~Light()
{
	glUseProgram(material_);
	std::string numLightsName = "numLights";
	GLint numLightsIndex = glGetUniformLocation(material_, numLightsName.c_str());
	int numLights;
	glGetUniformiv(material_, numLightsIndex, &numLights);
	numLights--;
	glUniform1i(numLightsIndex, numLights);
}

std::string game::Light::GetUniformName()
{
	return uniformName;
}

float game::Light::GetRange()
{
	return range;
}

glm::vec3 game::Light::GetSpecularColor()
{
	return specularColor;
}

void game::Light::SetRange(float value)
{
	glUseProgram(material_);
	range = value;
	glUniform1f(rangeIndex, range);
}

void game::Light::SetSpecularColor(glm::vec3 value)
{
	glUseProgram(material_);
	specularColor = value;
	glUniform3f(specColorIndex, value[0], value[1], value[2]);
}

void game::Light::SetPosition(glm::vec3 value)
{
	glUseProgram(material_);
	SceneNode::SetPosition(value);
	glUniform3f(positionIndex , value[0], value[1], value[2]);
}
