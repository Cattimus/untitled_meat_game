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

#include "objects/Shader.hpp"
#include "objects/Entity.hpp"
#include "Globals.hpp"
#include "UI.hpp"

const int width = 1600;
const int height = 900;

//set up values for camera
glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	auto window = glfwCreateWindow(width, height, "Untitled Meat Game", NULL, NULL);
	glfwMakeContextCurrent(window);

	//load extensions
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init GLAD" << std::endl;
		return -1;
	}

	//enable vsync
	glViewport(0, 0, width, height);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//set up shaders
	auto main_shader = new Shader("../src/shaders/main.vs", "../src/shaders/main.fs", "main_shader");
	auto testure = new Texture("../assets/discord.png", GL_LINEAR, "cat_texture");
	auto temptex = new Texture("../assets/crep.png", GL_LINEAR, "crep_texture");
	Entity test = Entity(main_shader, testure, "test_cube");

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	UI temp;
	//temp.demo = true;
	temp.info = true;

	double last_frame = glfwGetTime();
	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();

		main_shader->use();
		main_shader->set_mat4f("projection", projection);
		main_shader->set_mat4f("view", view);
		test.rotate(glm::vec3(0.5, 1, 0.01));

		main_shader->set_mat4f("model", test.get_model());
		test.render();
		temp.draw();
		glfwSwapBuffers(window);

		frame_time = glfwGetTime() - last_frame;
		last_frame = glfwGetTime();
		fps = round(1000 / (frame_time * 1000));
	}

	delete main_shader;

	ImGui::DestroyContext();
	glfwTerminate();
}
