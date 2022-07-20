#pragma once

#include "Position.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

class Entity : public Position
{
private:
	Mesh mesh;
	Shader* shader;
	Texture* texture;

public:

	Entity(Shader* objShader, Texture* objTexture)
	{
		shader = objShader;
		texture = objTexture;
	}
	
	//render the current object
	void render()
	{
		texture->use();
		mesh.draw();
	}
};
