#pragma once

#include <stddef.h>
#include <stdlib.h>
#include "glad/glad.h"
#include "imgui.h"
#include "glm/glm.hpp"

class Mesh
{
private:
	float* mesh;
	size_t vert_count;

	unsigned int VAO; //openGL ids for our mesh
	unsigned int VBO;

	//initialize buffers
	void bind_buffers();

	float* copy_vertex3f(float* dest, glm::vec3 src)
	{
		dest[0] = src.x;
		dest[1] = src.y;
		dest[2] = src.z;

		return (dest + 3);
	}

	float* copy_tex2f(float* dest, float l, float r)
	{
		dest[0] = l;
		dest[1] = r;

		return (dest + 2);
	}

	void make_cube(glm::vec3 size);
	
public:
	Mesh()
	{
		make_cube(glm::vec3(1, 1, 1));
		bind_buffers();
	}

	~Mesh()
	{
		free(mesh);
		mesh = NULL;
	}

	//return pointer to mesh
	float* mesh_ptr()
	{
		return mesh;
	}

	unsigned int get_VAO()
	{
		return VAO;
	}

	unsigned int get_VBO()
	{
		return VBO;
	}

	size_t get_vertcount()
	{
		return vert_count;
	}

	//draw mesh
	void draw()
	{
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, vert_count);
		glBindVertexArray(0);
	}
};
