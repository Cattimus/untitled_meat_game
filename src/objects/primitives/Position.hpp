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
	void moveTo(float x, float y, float z)
	{
		offset.x = x;
		offset.y = y;
		offset.z = z;
	}

	//set offset to an absolute value
	void moveTo(glm::vec3 to)
	{
		offset = to;
	}

	//origin move functions
	void moveOrigin(float x, float y, float z)
	{
		origin.x += x;
		origin.y += y;
		origin.z += z;
	}

	//move origin relative to it's current position
	void moveOrigin(glm::vec3 to)
	{
		origin += to;
	}

	//set origin to an absolute value
	void moveOriginTo(float x, float y, float z)
	{
		origin.x = x;
		origin.y = y;
		origin.z = z;
	}

	//move origin to absolute vec3
	void moveOriginTo(glm::vec3 to)
	{
		origin = to;
	}

	//set rotation values
	void rotate(glm::vec3 to)
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
	void resetPosition()
	{
		offset = origin;
	}

	//reset rotation variables
	void resetRotation()
	{
		rotation = glm::vec3(0, 0, 0);
	}

	//return current position of object
	glm::vec3 getPos()
	{
		return origin + offset;
	}

	//get origin of object
	glm::vec3 getOrigin()
	{
		return origin;
	}

	//get offset of object
	glm::vec3 getOffset()
	{
		return offset;
	}

	//return a model matrix that has been transformed to the correct values
	glm::mat4 getModel()
	{
		glm::mat4 model = glm::translate(model, origin + offset);
		model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0, 0));
		model = glm::rotate(model, rotation.y, glm::vec3(0, 1.0f, 0));
		model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1.0f));
		return model;
	}
};
