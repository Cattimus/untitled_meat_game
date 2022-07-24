#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "references.hpp"
#include "data/shader.hpp"
#include "data/position.hpp"

class Camera : public Position
{
private:

public:
	glm::mat4 projection;
	glm::mat4 view;
	float fov;

	Camera()
	{
		projection = glm::perspective(glm::radians(45.0f),
		(float)References::width / (float)References::height,
		0.1f, 100.0f);

		view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
	}

	void use(Shader* shader)
	{
		shader->set_mat4f("projection", projection);
		shader->set_mat4f("view", view);
	}

};