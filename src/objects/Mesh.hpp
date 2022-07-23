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
	void bind_buffers()
	{
		//initialize objects
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		//bind buffers
		glBindVertexArray(VAO);

		//assign buffer data
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vert_count * 5, mesh, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}

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

	//draw mesh
	void draw()
	{
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, vert_count);
		glBindVertexArray(0);
	}

	void debug_frame()
	{
		ImGui::Text("VAO ID: %d", VAO);
		ImGui::Text("VBO ID: %d", VBO);
		ImGui::Text("Vertexes:  %ld", vert_count);
	}
};
