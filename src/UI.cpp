#include "UI.hpp"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "objects/entity.hpp"
#include "objects/shader.hpp"
#include "objects/texture.hpp"
#include "references.hpp"
#include "limits"

void UI::mesh_frame(Mesh* a)
{
	ImGui::Text("VAO ID: %d", a->get_VAO());
	ImGui::Text("VBO ID: %d", a->get_VBO());
	ImGui::Text("Vertexes:  %ld", a->get_vertcount());
}

void UI::shader_frame(Shader* a)
{
	if(ImGui::TreeNode(a->get_name().c_str()))
	{
		ImGui::Text("Shader ID: %d", a->get_id());
		ImGui::Text("Valid: %d", a->is_valid());
		ImGui::Text("Address: %p", this);
		ImGui::TreePop();
	}
}

void UI::texture_frame(Texture* a)
{
	if(ImGui::TreeNode(a->get_name().c_str()))
		{
			ImGui::Text("Filename: %s", a->get_filename().c_str());
			ImGui::Text("Width: %d", a->get_width());
			ImGui::Text("Height: %d", a->get_height());
			ImGui::Text("Channels: %d", a->get_channels());
			ImGui::Text("Address: %p", this);
			ImGui::Text("Opengl Texture ID: %d", a->get_id());
			ImGui::TreePop();
		}
}

//TODO - allow editing of position and rotation
void UI::entity_frame(Entity* a)
{
	if(ImGui::TreeNode(a->get_name().c_str()))
	{
		glm::vec3* pos = a->get_offset_ptr();
		glm::vec3* rot = a->get_rotation_ptr();
		ImGui::Text("ID: %p", this);

		if(ImGui::TreeNode("Position"))
		{
			ImGui::DragFloat("x", &pos->x, 0.005f, -100000, 100000, "%.3f");
			ImGui::DragFloat("y", &pos->y, 0.005f, -100000, 100000, "%.3f");
			ImGui::DragFloat("z", &pos->z, 0.005f, -100000, 100000, "%.3f");
			ImGui::TreePop();
		}

		if(ImGui::TreeNode("Rotation"))
		{
			ImGui::DragFloat("x", &rot->x, 1.0f, -360.0f, 360.0f, "%.3f");
			ImGui::DragFloat("y", &rot->y, 1.0f, -360.0f, 360.0f, "%.3f");
			ImGui::DragFloat("z", &rot->z, 1.0f, -360.0f, 360.0f, "%.3f");
			a->rotate(glm::vec3(0,0,0));
			ImGui::TreePop();
		}

		if(ImGui::TreeNode("Shaders"))
		{
			int selected_index = 0;
			for(auto shader_tmp : References::shaders)
			{
				if(shader_tmp == a->get_shader())
				{
					break;
				}
				else
				{
					selected_index++;
				}
			}

			if(ImGui::BeginCombo("Shader", a->get_shader()->get_name().c_str()))
			{
				int counter = 0;
				for(auto shader_tmp : References::shaders)
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

			ImGui::TreePop();
		}

		if(ImGui::TreeNode("Textures"))
		{
			int selected_index = 0;
			for(auto tex_tmp : References::textures)
			{
				if(tex_tmp == a->get_texture())
				{
					break;
				}
				else
				{
					selected_index++;
				}
			}

			if(ImGui::BeginCombo("Texture", a->get_texture()->get_name().c_str()))
			{
				int counter = 0;
				for(auto tex_tmp : References::textures)
				{
					const bool is_selected = (counter == selected_index);
					if(ImGui::Selectable(tex_tmp->get_name().c_str(), is_selected))
					{
						a->set_texture(References::textures.at(counter));
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

			ImGui::TreePop();
		}
		
		if(ImGui::TreeNode("Mesh"))
		{
			mesh_frame(a->get_mesh());
			ImGui::TreePop();
		}

		ImGui::TreePop();
	}
}

void UI::draw()
{
	bool has_rendered = false;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if(demo)
	{
		ImGui::ShowDemoWindow(&demo);

		has_rendered = true;
	}

	if(info)
	{
		
		ImGui::Begin("Info");

		if(ImGui::TreeNode("Program"))
		{
			ImGui::Text("Fps: %d", References::fps);
			ImGui::Text("Last frame time: %fms", References::frame_time * 1000);
			ImGui::TreePop();
		}

		if(ImGui::TreeNode("Objects"))
		{
			for(auto obj : References::objects)
			{
				entity_frame(obj);
			}
			ImGui::TreePop();
		}

		if(ImGui::TreeNode("Shaders"))
		{
			for(auto shader : References::shaders)
			{
				shader_frame(shader);
			}
			ImGui::TreePop();
		}

		if(ImGui::TreeNode("Textures"))
		{
			for(auto texture : References::textures)
			{
				texture_frame(texture);
			}

			ImGui::TreePop();
		}
		ImGui::End();

		has_rendered = true;
	}

	ImGui::EndFrame();

	if(has_rendered)
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}