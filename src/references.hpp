#pragma once

#include <vector>

class Entity;
class Shader;
class Texture;
class Camera;

//TODO - make sure to delete objects from the vectors when they are deleted (destructor)

class References
{
public:
	static int fps;
	static double frame_time;
	static int width;
	static int height;
	static Camera* main_camera;
	static std::vector<Entity*> objects;
	static std::vector<Shader*> shaders;
	static std::vector<Texture*> textures;
};