#pragma once
#include <GLFW/glfw3.h>
#include "../include/glad/glad.h"
#include <stdexcept>
#include "camera.h"


using namespace camera;

namespace window {
	typedef void (* resize_callback)(int width, int height);
	typedef struct {
		float x;
		float y;
	} position;

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
			};

			void process_input(Camera& camera, float delta_time)
			{
				// Camera controls
				if (glfwGetKey(nativewindow, GLFW_KEY_W) == GLFW_PRESS)
					camera.processKeyboard(Camera_movement::FORWARD, delta_time);
				if (glfwGetKey(nativewindow, GLFW_KEY_S) == GLFW_PRESS)
					camera.processKeyboard(Camera_movement::BACKWARD, delta_time);
				if (glfwGetKey(nativewindow, GLFW_KEY_A) == GLFW_PRESS)
					camera.processKeyboard(Camera_movement::LEFT, delta_time);
				if (glfwGetKey(nativewindow, GLFW_KEY_D) == GLFW_PRESS)
					camera.processKeyboard(Camera_movement::RIGHT, delta_time);
			}

			position get_mouse_delta() {
				double xpos, ypos;
				glfwGetCursorPos(nativewindow, &xpos, &ypos);
				static double lastX = 0, lastY = 0;
				static bool firstMouse = true;

				if (firstMouse)
				{
					lastX = xpos;
					lastY = ypos;
					firstMouse = false;
				}

				double xoffset = xpos - lastX;
				double yoffset = lastY - ypos;
				lastX = xpos;
				lastY = ypos;

				// update camera orientation based on mouse movement
				return {
					(float)xoffset, (float)yoffset
				};
			}
			float deltatime()
			{
				float new_time = static_cast<float>(glfwGetTime());
				float deltatime = old_time - new_time;
				old_time = new_time;
				return deltatime;
			};
			void set_resize_callback(GLFWframebuffersizefun callback) {
				glfwSetFramebufferSizeCallback(nativewindow, callback);
			};
		private:
			float old_time;
			void load_glad() {
				if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
					throw std::runtime_error("failed loading gladloader");}
	};
}
