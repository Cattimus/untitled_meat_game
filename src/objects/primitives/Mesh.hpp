#pragma once

#include <stddef.h>
#include <stdlib.h>
#include "glad/glad.h"

//TODO - include texture coordinates?

class Mesh
{
private:
	float* mesh;
	size_t vert_count;
	size_t dimensions;

	unsigned int VAO; //openGL ids for our mesh
	unsigned int VBO;

	//initialize buffers
	void bind_buffers()
	{
		//initialize objects
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		//bind buffers
		glBindVertexArray(VAO);

		//assign buffer data
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vert_count * dimensions, mesh, GL_STATIC_DRAW);
		glVertexAttribPointer(0, dimensions, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
	}

	//update buffer data
	void update_buffers()
	{
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * vert_count * dimensions, mesh);

		glBindVertexArray(0);
	}
	
public:
	Mesh()
	{
		dimensions = 2;
		vert_count = 6;
		mesh = (float*)malloc(sizeof(float) * vert_count * dimensions);

		//left triangle
		mesh[0] = -0.5f; mesh[1] =  0.5f;
		mesh[2] = -0.5f; mesh[3] = -0.5f;
		mesh[4] =  0.5f; mesh[5] = -0.5f;

		//right triangle
		mesh[6]  =  0.5f; mesh[7]  =  0.5f;
		mesh[8]  =  0.5f; mesh[9]  = -0.5f;
		mesh[10] = -0.5f; mesh[11] =  0.5f;

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

	//draw mesh
	void draw()
	{
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, vert_count);
	}
};
