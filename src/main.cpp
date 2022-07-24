#include <iostream>
#include <math.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

//imgui includes
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "data/shader.hpp"
#include "scene/entity.hpp"
#include "scene/camera.hpp"
#include "UI.hpp"
#include "references.hpp"

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	auto window = glfwCreateWindow(References::width, References::height, "Untitled Meat Game", NULL, NULL);
	glfwMakeContextCurrent(window);

	//load extensions
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, References::width, References::height);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//set up camera
	Camera main_camera;

	//set up shaders
	auto main_shader = new Shader("../src/shaders/main.vs", "../src/shaders/main.fs", "main_shader");
	auto testure = new Texture("../assets/discord.png", GL_LINEAR, "cat_texture");
	auto temptex = new Texture("../assets/crep.png", GL_LINEAR, "crep_texture");
	Entity test = Entity(main_shader, testure, "test_cube");
	Entity test2 = Entity(main_shader, temptex, "test_cube2");
	test.move(glm::vec3(-0.5, 0, 0));
	test2.move(glm::vec3(0.5, 0, 0));

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	UI temp;
	//temp.demo = true;
	//temp.objects = true;
	temp.debug = true;

	double last_frame = glfwGetTime();
	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		main_shader->use();
		main_camera.use(main_shader);

		test.render();
		test2.render();
		temp.draw();
		glfwSwapBuffers(window);
		glfwPollEvents();

		References::frame_time = glfwGetTime() - last_frame;
		last_frame = glfwGetTime();
		References::fps = round(1000 / (References::frame_time * 1000));
	}

	delete main_shader;

	ImGui::DestroyContext();
	glfwTerminate();
}
