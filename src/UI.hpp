#pragma once

#include "scene/entity.hpp"
#include "data/shader.hpp"
#include "data/texture.hpp"

class UI
{
private:
	void entity_frame(Entity* a);
	void shader_frame(Shader* a);
	void texture_frame(Texture* a);
	void mesh_frame(Mesh* a);

public:
	bool demo = false;
	bool info = false;

	void draw();
};