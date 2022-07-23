#pragma once

#include "objects/entity.hpp"
#include "objects/shader.hpp"
#include "objects/texture.hpp"

class UI
{
private:
	void entity_frame(Entity* a);
	void shader_frame(Shader* a);
	void texture_frame(Texture* a);

public:
	bool demo = false;
	bool info = false;

	void draw();
};