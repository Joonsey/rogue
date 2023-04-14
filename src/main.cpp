#include "../include/glad/glad.h"
#include "../include/glm/glm.hpp"
#include "../include/glm/ext.hpp"
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <cmath>
#include "shader.h"
#include "rectangle.h"
#include "cube.h"

#define WIDTH 800
#define HEIGHT 600


GLFWwindow* create_window()
{
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		throw std::runtime_error("failed creating window");
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error("failed loading gladloader");
	}
	return window;
}

void processInput(GLFWwindow *window, Rectangle* player = nullptr)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, true);

	if (player == nullptr) return;

    if(glfwGetKey(window, GLFW_KEY_A))
		player->Move(glm::vec2(-0.1f, 0.f));

    if(glfwGetKey(window, GLFW_KEY_W))
		player->Move(glm::vec2(0.f, 0.1f));

    if(glfwGetKey(window, GLFW_KEY_S))
		player->Move(glm::vec2(0.f, -0.1f));

    if(glfwGetKey(window, GLFW_KEY_D))
		player->Move(glm::vec2(0.1f, 0.f));

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                            GLsizei length, const GLchar* message, const void* userParam)
{
    // print debug message to console
    std::cout << "OpenGL Debug: " << message << std::endl;
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

	GLFWwindow* window = create_window();
	Shader shaderProgram = Shader("src/shaders/vertex.glsl","src/shaders/fragment.glsl");

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	float time;
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
	while(!glfwWindowShouldClose(window))
	{
		processInput(window, &rect);

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

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
    return 0;
}
