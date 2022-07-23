#pragma once

#include <vector>

class Entity;
class Shader;
class Texture;

class References
{
public:
	static int fps;
	static double frame_time;
	static std::vector<Entity*> objects;
	static std::vector<Shader*> shaders;
	static std::vector<Texture*> textures;
};