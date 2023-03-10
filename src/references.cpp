#include "references.hpp"

#include "scene/entity.hpp"
#include "data/shader.hpp"
#include "data/texture.hpp"
#include "scene/camera.hpp"

int References::fps = 0;
float References::frame_time = 0;
int References::width = 1600;
int References::height = 900;
Camera* References::main_camera = NULL;
std::vector<Entity*> References::objects = std::vector<Entity*>();
std::vector<Shader*> References::shaders = std::vector<Shader*>();
std::vector<Texture*> References::textures = std::vector<Texture*>();