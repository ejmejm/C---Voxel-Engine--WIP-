#pragma once

#include <iostream>
#include<GL/glew.h>
#include <GLFW/glfw3.h>

namespace edan{
	namespace graphics{

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

		class Window{
		private:
			friend struct GLFWwindow;
			const char *m_Title;
			int m_Width, m_Height;
			GLFWwindow *m_Window;
			bool m_Closed;

			bool m_Keys[MAX_KEYS];
			bool m_MouseButtons[MAX_BUTTONS];
			double mx, my;
			double mxPrev, myPrev;
			double dmx, dmy;
		public:
			Window(const char *m_Title, int width, int height);
			~Window();
			bool closed() const;
			void update();
			void clear() const;

			inline void close() const { glfwSetWindowShouldClose(m_Window, GL_TRUE); }

			inline int getWidth() const { return m_Width;  };
			inline int getHeight() const { return m_Height;  };
			inline int getDeltaX() const { return dmx; };
			inline int getDeltaY() const { return dmy; };
			void deltaMouseUpdate();

			bool isKeyPressed(unsigned int keycode) const;
			bool isMouseButtonPressed(unsigned int button) const;
			void getMousePosition(double& x, double& y) const;
		private:
			bool init();
			friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		};
	}
}