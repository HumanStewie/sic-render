#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <print>
#include "window.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

Window::Window(int width, int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_GLFWwin = glfwCreateWindow(width, height, "[sic]render", nullptr, nullptr);

    if (m_GLFWwin == nullptr) {
        std::println("Did not initialize window correctly.");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(m_GLFWwin);

    glfwSetFramebufferSizeCallback(m_GLFWwin, framebuffer_size_callback);
}

Window::~Window() {
    glfwDestroyWindow(m_GLFWwin);
    glfwTerminate();
}