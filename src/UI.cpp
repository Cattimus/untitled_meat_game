#include "UI.hpp"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "scene/entity.hpp"
#include "data/shader.hpp"
#include "data/texture.hpp"
#include "references.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

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

void UI::camera_frame(Camera* a)
{
	glm::vec3* pos = a->get_offset_ptr();
	glm::vec3* rot = a->get_rotation_ptr();
	ImGui::Text("ID: %p", this);
	float FOV = a->get_fov();

	ImGui::DragFloat3("Position", glm::value_ptr(*pos), 0.005f, -100000, 100000, "%.3f");
	ImGui::DragFloat("FOV", &FOV, 1.0f, 0.0f, 10000.0f, "%.2f");
	ImGui::DragFloat3("Rotation", glm::value_ptr(*rot), 1.0f, -360, 360, "%.3f");
	
	a->rotate(glm::vec3(0,0,0));
	a->change_fov(FOV);

}

void UI::entity_frame(Entity* a)
{
	if(ImGui::TreeNode(a->get_name().c_str()))
	{
		glm::vec3* pos = a->get_offset_ptr();
		glm::vec3* rot = a->get_rotation_ptr();
		glm::vec3* vel = a->get_vl_ptr();
		glm::vec3* rotvel = a->get_rvl_ptr();
		ImGui::Text("ID: %p", this);
		ImGui::Checkbox("Visible", a->get_visible_ptr());

		ImGui::Text("Position");
		ImGui::DragFloat3("Position", glm::value_ptr(*pos), 0.005f, -100000, 100000, "%.3f");
		ImGui::DragFloat("Scale", a->get_scale_ptr(), 0.005f, 0, 100000, "%.3f");
		ImGui::DragFloat3("Rotation", glm::value_ptr(*rot), 1.0f, -360, 360, "%.3f");

		ImGui::Text("Velocity");
		ImGui::DragFloat3("Velocity", glm::value_ptr(*vel), 0.0005f, -1, 1, "%.3f");
		ImGui::DragFloat3("Rotation Velocity", glm::value_ptr(*rotvel), 1.0f, -720, 720, "%.3f");

		

		a->rotate(glm::vec3(0,0,0));

		//shader combo box
		int selected_shader_index = 0;
		for(auto shader_tmp : References::shaders)
		{
			if(shader_tmp == a->get_shader())
			{
				break;
			}
			else
			{
				selected_shader_index++;
			}
		}

		if(ImGui::BeginCombo("Shader", a->get_shader()->get_name().c_str()))
		{
			int counter = 0;
			for(auto shader_tmp : References::shaders)
			{
				const bool is_selected = (counter == selected_shader_index);
				if(ImGui::Selectable(shader_tmp->get_name().c_str(), is_selected))
				{
					selected_shader_index = counter;
				}

				if(is_selected)
				{
					ImGui::SetItemDefaultFocus();
				}

				counter++;
			}
			ImGui::EndCombo();
		}

		int selected_texture_index = 0;
		for(auto tex_tmp : References::textures)
		{
			if(tex_tmp == a->get_texture())
			{
				break;
			}
			else
			{
				selected_texture_index++;
			}
		}

		if(ImGui::BeginCombo("Texture", a->get_texture()->get_name().c_str()))
		{
			int counter = 0;
			for(auto tex_tmp : References::textures)
			{
				const bool is_selected = (counter == selected_texture_index);
				if(ImGui::Selectable(tex_tmp->get_name().c_str(), is_selected))
				{
					a->set_texture(References::textures.at(counter));
					selected_texture_index = counter;
				}

				if(is_selected)
				{
					ImGui::SetItemDefaultFocus();
				}

				counter++;
			}
			ImGui::EndCombo();
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
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if(debug)
	{
		ImGui::Begin("Debug", &debug);

		if(ImGui::Button("Show process info"))
		{
			info = true;
		}

		if(ImGui::Button("Show camera window"))
		{
			camera = true;
		}

		if(ImGui::Button("Show objects window")) 
		{
			objects = true;
		}

		if(ImGui::Button("Show textures window"))
		{
			textures = true;
		}

		if(ImGui::Button("Show shaders window"))
		{
			shaders = true;
		}

		if(ImGui::Button("Show demo"))
		{
			demo = true;
		}

		ImGui::End();
	}

	if(demo)
	{
		ImGui::ShowDemoWindow(&demo);
	}

	
	if(info)
	{
		ImGui::Begin("Info", &info);
		ImGui::Text("Fps: %d", References::fps);
		ImGui::Text("Last frame time: %fms", References::frame_time * 1000);
		ImGui::Text("Entity count: %ld", References::objects.size());
		ImGui::Text("Texture count: %ld", References::textures.size());
		ImGui::Text("Shader count: %ld", References::shaders.size());
		
		ImGui::End();
	}

	if(objects)
	{
		ImGui::Begin("Objects", &objects);
		for(auto obj : References::objects)
		{
			entity_frame(obj);
		}
		ImGui::End();
	}

	if(shaders)
	{
		ImGui::Begin("Shaders", &shaders);
		for(auto shader : References::shaders)
		{
			shader_frame(shader);
		}
		ImGui::End();
	}

	if(textures)
	{
		ImGui::Begin("Textures", &textures);
		for(auto texture : References::textures)
		{
			texture_frame(texture);
		}
		ImGui::End();
	}

	if(camera)
	{
		ImGui::Begin("Camera", &camera);
		camera_frame(References::main_camera);
		ImGui::End();
		
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}