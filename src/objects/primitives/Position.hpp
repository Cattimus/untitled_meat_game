#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Mesh.hpp"

class Position
{
private:
	glm::vec3 origin;
	glm::vec3 offset;
	glm::vec3 rotation;

public:
	Position()
	{
		origin   = glm::vec3(0, 0, 0);
		offset   = glm::vec3(0, 0, 0);
		rotation = glm::vec3(0, 0, 0);
	}

	//move relative to the current position
	void move(float x, float y, float z)
	{
		offset.x += x;
		offset.y += y;
		offset.z += z;
	}

	//move relative to the current position
	void move(glm::vec3 to)
	{
		offset += to;
	}

	//set offset to an absolute value
	void move_to(float x, float y, float z)
	{
		offset.x = x;
		offset.y = y;
		offset.z = z;
	}

	//set offset to an absolute value
	void move_to(glm::vec3 to)
	{
		offset = to;
	}

	//origin move functions
	void move_origin(float x, float y, float z)
	{
		origin.x += x;
		origin.y += y;
		origin.z += z;
	}

	//move origin relative to it's current position
	void move_origin(glm::vec3 to)
	{
		origin += to;
	}

	//set origin to an absolute value
	void move_origin_to(float x, float y, float z)
	{
		origin.x = x;
		origin.y = y;
		origin.z = z;
	}

	//move origin to absolute vec3
	void move_origin_to(glm::vec3 to)
	{
		origin = to;
	}

	//set rotation values
	void rotate(glm::vec3 to)
	{
		rotation += to;
	}

	void rotate_to(glm::vec3 to)
	{
		rotation = to;
	}

	//reset all values
	void reset()
	{
		offset = origin;
		rotation = glm::vec3(0, 0, 0);
	}

	//reset position variables
	void reset_position()
	{
		offset = origin;
	}

	//reset rotation variables
	void reset_rotation()
	{
		rotation = glm::vec3(0, 0, 0);
	}

	//return current position of object
	glm::vec3 get_pos()
	{
		return origin + offset;
	}

	//get origin of object
	glm::vec3 get_origin()
	{
		return origin;
	}

	//get offset of object
	glm::vec3 get_offset()
	{
		return offset;
	}

	//return a model matrix that has been transformed to the correct values
	glm::mat4 get_model()
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), (origin + offset));
		model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0, 0));
		model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1.0f, 0));
		model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1.0f));
		return model;
	}
};
