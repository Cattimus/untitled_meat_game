#include "Entity.hpp"

std::vector<Entity*> Entity::objects = std::vector<Entity*>();

void Entity::debug_frame()
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
			int selected_index = 0;
			for(auto shader_tmp : Shader::shaders)
			{
				if(shader_tmp == shader)
				{
					break;
				}
				else
				{
					selected_index++;
				}
			}

			if(ImGui::BeginCombo("Shader", shader->get_name().c_str()))
			{
				int counter = 0;
				for(auto shader_tmp : Shader::shaders)
				{
					const bool is_selected = (counter == selected_index);
					if(ImGui::Selectable(shader_tmp->get_name().c_str(), is_selected))
					{
						selected_index = counter;
					}

					if(is_selected)
					{
						ImGui::SetItemDefaultFocus();
					}

					counter++;
				}
				ImGui::EndCombo();
			}
		}

		if(ImGui::CollapsingHeader("Textures"))
		{
			int selected_index = 0;
			for(auto tex_tmp : Texture::textures)
			{
				if(tex_tmp == texture)
				{
					break;
				}
				else
				{
					selected_index++;
				}
			}

			if(ImGui::BeginCombo("Texture", texture->get_name().c_str()))
			{
				int counter = 0;
				for(auto tex_tmp : Texture::textures)
				{
					const bool is_selected = (counter == selected_index);
					if(ImGui::Selectable(tex_tmp->get_name().c_str(), is_selected))
					{
						texture = Texture::textures.at(counter);
						selected_index = counter;
					}

					if(is_selected)
					{
						ImGui::SetItemDefaultFocus();
					}

					counter++;
				}
				ImGui::EndCombo();
			}
		}

		if(ImGui::CollapsingHeader("Mesh"))
		{
			mesh.debug_frame();
		}


		ImGui::TreePop();
	}
}