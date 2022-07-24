#include "references.hpp"

#include "objects/entity.hpp"
#include "objects/shader.hpp"
#include "objects/texture.hpp"

int References::fps = 0;
double References::frame_time = 0;
int References::width = 1600;
int References::height = 900;
std::vector<Entity*> References::objects = std::vector<Entity*>();
std::vector<Shader*> References::shaders = std::vector<Shader*>();
std::vector<Texture*> References::textures = std::vector<Texture*>();