#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "references.hpp"
#include "data/shader.hpp"
#include "data/position.hpp"

class Camera : public Position
{
private:
	glm::mat4 projection;
	float fov;

public:

	Camera()
	{
		projection = glm::perspective(glm::radians(45.0f),
		(float)References::width / (float)References::height,
		0.1f, 100.0f);

		fov = 45;
	}

	void change_fov(float new_fov)
	{
		fov = new_fov;
		projection = glm::perspective(glm::radians(fov),
		(float)References::width / (float)References::height,
		0.1f, 100.0f);
	}

	float get_fov()
	{
		return fov;
	}

	float* get_fov_ptr()
	{
		return &fov;
	}

	void use(Shader* shader)
	{
		//calculate the pitch and yaw values. pitch is adjusted by 90 to start at 0
		glm::vec3 pyr(
		cos(glm::radians(rotation.x - 90)) * cos(glm::radians(rotation.y)),
		sin(glm::radians(rotation.y)),
		sin(glm::radians(rotation.x - 90)) * cos(glm::radians(rotation.y)));
		pyr = glm::normalize(pyr);

		shader->set_mat4f("projection", projection);
		shader->set_mat4f("view", glm::lookAt(get_pos(), get_pos() + pyr, glm::vec3(0,1,0)));
		//shader->set_mat4f("view", glm::translate(glm::mat4(1.0f), get_pos()));
	}

};