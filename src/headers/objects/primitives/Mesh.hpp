#pragma once

#include <stddef.h>
#include <stdlib.h>

class Mesh
{
private:
	float* mesh;
	size_t vert_count;
	size_t dimensions;
	
public:
	Mesh()
	{
		dimensions = 2;
		vert_count = 6;
		mesh = (float*)malloc(sizeof(float) * 12);

		//left triangle
		mesh[0] = -1.0f; mesh[1] =  1.0f;
		mesh[2] = -1.0f; mesh[3] = -1.0f;
		mesh[4] =  1.0f; mesh[5] = -1.0f;

		//right triangle
		mesh[6]  =  1.0f; mesh[7]  =  1.0f;
		mesh[8]  =  1.0f; mesh[9]  = -1.0f;
		mesh[10] = -1.0f; mesh[11] = -1.0f;
	}

	~Mesh()
	{
		free(mesh);
		mesh = NULL;
	}

	//calculate stride value
	size_t stride()
	{
		return dimensions * sizeof(float);
	}

	//return pointer to mesh
	float* mesh_ptr()
	{
		return mesh;
	}
};
