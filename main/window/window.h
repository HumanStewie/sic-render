#pragma once

#include <GLFW/glfw3.h>

class Window {
public:
	Window(int width, int height);
	~Window();
	bool WindowIsOpen() {
		return !glfwWindowShouldClose(m_GLFWwin);
	}
	GLFWwindow* GetWindow() {
		return m_GLFWwin;
	}
	void SwapBuffer() {
		glfwSwapBuffers(m_GLFWwin);
	}
	void PollEvent() {
		glfwPollEvents();
	}
	void CloseWindow() {
		glfwSetWindowShouldClose(m_GLFWwin, true);
	}
	
private:
	GLFWwindow* m_GLFWwin{nullptr};
};