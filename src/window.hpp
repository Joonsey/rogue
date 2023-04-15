#pragma once
#include <GLFW/glfw3.h>
#include "../include/glad/glad.h"
#include <stdexcept>

typedef void (* resize_callback)(int width, int height);

class Window {
public:
	GLFWwindow* nativewindow;
	const int width;
	const int height;
    Window(unsigned int width, unsigned int height, const char* title )
		: height(height), width(width)
	{
		// creates glfw window
		nativewindow = glfwCreateWindow(width, height, title, NULL, NULL);
		if (nativewindow  == NULL)
		{
			glfwTerminate();
			throw std::runtime_error("failed creating window");
		}

		// makes current window the opengl context
		glfwMakeContextCurrent(nativewindow);

		// load glad from current context
		load_glad();

    }

	void set_resize_callback(GLFWframebuffersizefun callback) {
		glfwSetFramebufferSizeCallback(nativewindow, callback);
	}
private:
	void load_glad() {
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			throw std::runtime_error("failed loading gladloader");}
};
