#pragma once

#include "Position.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>

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

	//adds the appropriate debug info to the debug UI frame
	void debug_info()
	{
		if(ImGui::TreeNode(name.c_str()))
		{
			glm::vec3 pos = get_pos();
			glm::vec3 rot = get_rotation();

			if(ImGui::BeginTable("info_table", 2, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner))
			{
				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Name:");
				ImGui::TableNextColumn();
				ImGui::Text("%s", name.c_str());

				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("ID:");
				ImGui::TableNextColumn();
				ImGui::Text("%p", this);

				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Texture:");
				ImGui::TableNextColumn();
				ImGui::Text("%p", texture);

				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Shader:");
				ImGui::TableNextColumn();
				ImGui::Text("%p", shader);

				ImGui::EndTable();
			}

			if(ImGui::CollapsingHeader("Position"))
			{
				ImGui::Text("x: %f", pos.x);
				ImGui::Text("y: %f", pos.y);
				ImGui::Text("z: %f", pos.z);
			}

			if(ImGui::CollapsingHeader("Rotation"))
			{
				ImGui::Text("x: %f", rot.x);
				ImGui::Text("y: %f", rot.y);
				ImGui::Text("z: %f", rot.z);
			}


			ImGui::TreePop();
		}
	}
};
