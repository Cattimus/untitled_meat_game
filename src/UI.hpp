#pragma once

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "../../Globals.hpp"

class UI
{
private:

public:
	bool demo = false;
	bool info = false;


	void draw();
};