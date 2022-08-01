#pragma once

#include "glm/glm.hpp"
#include "data/position.hpp"
#include "references.hpp"

class Movement : public Position
{
protected:
glm::vec3 velocity;
glm::vec3 rotation_velocity;

public:
	Movement()
	{
		velocity = glm::vec3(0,0,0);
		rotation_velocity = glm::vec3(0,0,0);
	}


	//move based on delta time and velocity
	void update_position()
	{
		offset += (velocity * References::frame_time);
		rotation += (rotation_velocity * References::frame_time);
	}

	void set_velocity(glm::vec3 new_velocity)
	{
		velocity = new_velocity;
	}

	void set_rotation_velocity(glm::vec3 new_velocity)
	{
		rotation_velocity = new_velocity;
	}

	glm::vec3 get_velocity()
	{
		return velocity;
	}

	glm::vec3 get_rotation_velocity()
	{
		return rotation_velocity;
	}

	glm::vec3* get_vl_ptr()
	{
		return &velocity;
	}

	glm::vec3* get_rvl_ptr()
	{
		return &rotation_velocity;
	}
};