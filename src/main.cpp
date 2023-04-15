#include "../include/glad/glad.h"
#include "../include/glm/glm.hpp"
#include "../include/glm/ext.hpp"
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <cmath>
#include "shader.h"
#include "rectangle.h"
#include "cube.h"
#include "window.hpp"

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
	glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

	Window window(WIDTH, HEIGHT, "rogue");
	Shader shaderProgram = Shader("src/shaders/vertex.glsl","src/shaders/fragment.glsl");

	window.set_resize_callback(framebuffer_size_callback);

	Rectangle rect(
			glm::vec2(0.5f, 0.5f),
			glm::vec2(0.5f, 0.5f),
			glm::vec3(1.0f, 0.0f, 0.0f));

	Cube cube(
			glm::vec3(-0.5f, -0.5f, -1.f),
			1.f,
			glm::vec3(0.0f, 2.0f, 1.0f));

	Cube cube2(
			glm::vec3(0.5f, 0.5f, -1.f),
			1.f,
			glm::vec3(0.0f, 2.0f, 1.0f));


	glEnable(GL_DEPTH_TEST);
	while(!glfwWindowShouldClose(window.nativewindow))
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//model = glm::rotate(model,  glm::radians(50.0f) / 20, glm::vec3(0.5f, 1.0f, 0.0f));
		shaderProgram.use();
		shaderProgram.setMat4f("projection", proj);
		shaderProgram.setMat4f("view", view);
		shaderProgram.setMat4f("model", model);

		rect.Render();
		cube.Render();
		cube2.Render();

		glfwSwapBuffers(window.nativewindow);

		glfwPollEvents();
	}

	glfwTerminate();
    return 0;
}
