#pragma once

#include "Position.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

class Entity : public Position
{
private:
	Mesh mesh;
	Shader* shader;
	Texture* texture;
	std::string name;

public:

	Entity(Shader* objShader, Texture* objTexture, std::string objName)
	{
		shader = objShader;
		texture = objTexture;
		name = objName;
	}
	
	//render the current object
	void render()
	{
		texture->use();
		mesh.draw();
	}

	//TODO - allow user to change values from the debug UI
	//adds the appropriate debug info to the debug UI frame
	void debug_frame()
	{
		if(ImGui::TreeNode(name.c_str()))
		{
			glm::vec3 pos = get_pos();
			glm::vec3 rot = get_rotation();

			ImGui::Text("ID: %p", this);

			if(ImGui::CollapsingHeader("Position", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Text("x: %f", pos.x);
				ImGui::Text("y: %f", pos.y);
				ImGui::Text("z: %f", pos.z);
			}

			if(ImGui::CollapsingHeader("Rotation", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Text("x: %f", rot.x);
				ImGui::Text("y: %f", rot.y);
				ImGui::Text("z: %f", rot.z);
			}

			if(ImGui::CollapsingHeader("Shaders"))
			{
				shader->debug_frame();
			}

			if(ImGui::CollapsingHeader("Textures"))
			{
				texture->debug_frame();
			}

			if(ImGui::CollapsingHeader("Mesh"))
			{
				mesh.debug_frame();
			}


			ImGui::TreePop();
		}
	}
};
