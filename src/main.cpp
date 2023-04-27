#include "../include/glad/glad.h"
#include "../include/glm/glm.hpp"
#include "../include/glm/ext.hpp"
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <cmath>
#include "shader.h"
#include "rectangle.h"
#include "cube.h"
#include "window.h"
#include "camera.h"
#include "entity_manager.h"
#include "entity.h"
#include "map.h"
#include "tile.h"

#define WIDTH 800
#define HEIGHT 600


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float) WIDTH /(float) HEIGHT, 0.1f, 100.0f);
	glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(-0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

	window::Window window(WIDTH, HEIGHT, "rogue");
	shader::Shader shaderProgram("src/shaders/vertex.glsl","src/shaders/fragment.glsl");
	camera::Camera camera(
			glm::vec3(0.0f, 3.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			-90.0f,
			-45.0f);

	window.set_resize_callback(framebuffer_size_callback);

	world::Map world_map;
	EM::EntityManager entity_manager;

	world::MAP_DATA world_data = {
		{1, 1, 1},
		{3, 1, 1},
		{4, 1, 1},
		{5, 1, 1},
		{6, 1, 1},
		{7, 1, 1},
		{2, 1, 2},
		{2, 1, 3},
		{2, 1, 4},
		{2, 1, 5},
		{2, 2, 6}
	};

	world_map.seed_world(world_data);

	camera.freecam = false;

	glEnable(GL_DEPTH_TEST);
	while(!glfwWindowShouldClose(window.nativewindow))
	{
		auto mouse_delta = window.get_mouse_delta();
		camera.processMouseMovement(mouse_delta.x, mouse_delta.y, true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		shaderProgram.use();
		shaderProgram.setMat4f("projection", proj);
		shaderProgram.setMat4f("view", camera.getViewMatrix());
		shaderProgram.setMat4f("model", model);
		window.process_input(camera, window.deltatime());

		world_map.render_tiles();
		entity_manager.render_entites();


		glfwSwapBuffers(window.nativewindow);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
