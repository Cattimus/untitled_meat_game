#include "UI.hpp"

#include "../Entity.hpp"
#include "../Shader.hpp"
#include "../Texture.hpp"

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
			ImGui::Text("Fps: %d", fps);
			ImGui::Text("Last frame time: %fms", frame_time * 1000);
			ImGui::TreePop();
		}

		if(ImGui::TreeNode("Objects"))
		{
			for(auto obj : Entity::objects)
			{
				obj->debug_frame();
			}
			ImGui::TreePop();
		}

		if(ImGui::TreeNode("Shaders"))
		{
			for(auto shader : Shader::shaders)
			{
				shader->debug_frame();
			}
			ImGui::TreePop();
		}

		if(ImGui::TreeNode("Textures"))
		{
			for(auto texture : Texture::textures)
			{
				texture->debug_frame();
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