#pragma once

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

class UI
{
private:
	Entity* debug_target;
	bool info = false;

public:
	bool demo = false;
	
	UI()
	{
		debug_target = NULL;
	}

	void debug(Entity* target)
	{
		debug_target = target;
		info = true;
	}

	void draw()
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
			if(ImGui::TreeNode("Objects"))
			{
				if(debug_target != NULL)
				{
					debug_target->debug_info();
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
};