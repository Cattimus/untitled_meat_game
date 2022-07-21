#pragma once

#include <stddef.h>
#include <stdlib.h>
#include "glad/glad.h"

class Mesh
{
private:
	float* mesh;
	float* tex_mesh;
	int* indexes;
	size_t vert_count;
	size_t dimensions;
	size_t index_count;

	unsigned int VAO; //openGL ids for our mesh
	unsigned int VBO;
	unsigned int EBO;
	unsigned int TEX;

	//initialize buffers
	void bind_buffers()
	{
		//initialize objects
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenBuffers(1, &TEX);

		//bind buffers
		glBindVertexArray(VAO);

		//assign buffer data
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vert_count * dimensions, mesh, GL_STATIC_DRAW);
		glVertexAttribPointer(0, dimensions, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, TEX);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vert_count * 2, tex_mesh, GL_STATIC_DRAW);
		glVertexAttribPointer(1, dimensions, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * index_count, indexes, GL_STATIC_DRAW);

		glBindVertexArray(0);
	}

	void make_cube(glm::vec3 size)
	{
		dimensions = 3;
		vert_count = 8;
		index_count = 36;

		mesh = (float*)malloc(sizeof(float) * vert_count * dimensions);
		tex_mesh = (float*)malloc(sizeof(float) * vert_count * 2);
		indexes = (int*)malloc(sizeof(int) * index_count);

		float width  = size.x / (float)2;
		float height = size.y / (float)2;
		float depth = size.z / (float)2;

		float nwidth = width * -1;
		float nheight = height * -1;
		float ndepth = depth * -1;

		//vertexes												 //texture coords
		mesh[0]  = nwidth; mesh[1]  = height; mesh[2]  = ndepth; tex_mesh[0]  = 0; tex_mesh[1]  = 0; //upper front left
		mesh[3]  = width;  mesh[4]  = height; mesh[5]  = ndepth; tex_mesh[2]  = 1; tex_mesh[3]  = 0; //upper front right
		mesh[6]  = width;  mesh[7]  = height; mesh[8]  = depth;  tex_mesh[4]  = 1; tex_mesh[5]  = 1; //upper back right
		mesh[9]  = nwidth; mesh[10] = height; mesh[11] = depth;  tex_mesh[6]  = 0; tex_mesh[7]  = 1; //upper back left

		mesh[12] = nwidth; mesh[13] = nheight; mesh[14] = ndepth; tex_mesh[8]  = 1; tex_mesh[9]  = 1; //lower front left
		mesh[15] = width;  mesh[16] = nheight; mesh[17] = ndepth; tex_mesh[10] = 0; tex_mesh[11] = 1; //lower front right
		mesh[18] = width;  mesh[19] = nheight; mesh[20] = depth;  tex_mesh[12] = 0; tex_mesh[13] = 0; //lower back right
		mesh[21] = nwidth; mesh[22] = nheight; mesh[23] = depth;  tex_mesh[14] = 1; tex_mesh[15] = 0; //lower back left

		//indexes
		indexes[0]  = 0; indexes[1]  = 1; indexes[2]  = 2;
		indexes[3]  = 2; indexes[4]  = 3; indexes[5]  = 0; //top
		indexes[6]  = 3; indexes[7]  = 2; indexes[8]  = 6;
		indexes[9]  = 6; indexes[10] = 7; indexes[11] = 3; //back
		indexes[12] = 7; indexes[13] = 6; indexes[14] = 5;
		indexes[15] = 5; indexes[16] = 4; indexes[17] = 7; //bottom
		indexes[18] = 4; indexes[19] = 7; indexes[20] = 3;
		indexes[21] = 3; indexes[22] = 0; indexes[23] = 4; //left
		indexes[24] = 0; indexes[25] = 1; indexes[26] = 5;
		indexes[27] = 0; indexes[28] = 4; indexes[29] = 5; //front
		indexes[30] = 1; indexes[31] = 2; indexes[32] = 6;
		indexes[33] = 6; indexes[34] = 5; indexes[35] = 1; //right
	}
	
public:
	Mesh()
	{
		make_cube(glm::vec3(1.5, 1, 1));
		bind_buffers();
	}

	~Mesh()
	{
		free(mesh);
		mesh = NULL;

		free(tex_mesh);
		tex_mesh = NULL;
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
		glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
};
