#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <cmath>
#include "shader.h"
#include "rectangle.h"

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

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, true);
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

	GLFWwindow* window = create_window();
	Shader shaderProgram = Shader("src/shaders/vertex.glsl","src/shaders/fragment.glsl");

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	float time;
	Rectangle rect(
			glm::vec2(0.5f, 0.5f),
			glm::vec2(0.5f, 0.5f),
			glm::vec3(1.0f, 0.0f, 0.0f));

	Rectangle rect2(
			glm::vec2(-0.5f, -0.5f),
			glm::vec2(0.5f, 0.5f),
			glm::vec3(0.0f, 0.0f, 1.0f));

	while(!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		shaderProgram.use();

		rect.Render();
		rect2.Render();


		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
    return 0;
}
