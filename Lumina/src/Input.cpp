#include "Input.h"

#include "Camera.h"
#include "Window.h"
#include <GLFW/glfw3.h>

Input::Input(Window& window, Camera& camera) : m_window(window), m_camera(camera) {
	glfwSetWindowUserPointer(m_window.GetHandle(), this);
	lastX = m_window.GetWidth() / 2.0f;
	lastY = m_window.GetHeight() / 2.0f;
}

Input::~Input() {
	glfwSetWindowUserPointer(m_window.GetHandle(), nullptr);
}

void Input::ProcessKeyboard(float deltaTime) {
	if (glfwGetKey(m_window.GetHandle(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window.GetHandle(), true);
	if (glfwGetKey(m_window.GetHandle(), GLFW_KEY_W) == GLFW_PRESS)
		m_camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(m_window.GetHandle(), GLFW_KEY_S) == GLFW_PRESS)
		m_camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(m_window.GetHandle(), GLFW_KEY_A) == GLFW_PRESS)
		m_camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(m_window.GetHandle(), GLFW_KEY_D) == GLFW_PRESS)
		m_camera.ProcessKeyboard(RIGHT, deltaTime);
}

void Input::ProcessMouseMovement(double xposIn, double yposIn) {
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	m_camera.ProcessMouseMovement(xoffset, yoffset);
}

void Input::MouseCallback(GLFWwindow* window, double xpos, double ypos) {
	Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
	if (input) {
		input->ProcessMouseMovement(xpos, ypos);
	}
}

void Input::ProcessMouseScroll(double xoffset, double yoffset) {
	m_camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void Input::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
	if (input) {
		input->ProcessMouseScroll(xoffset, yoffset);
	}
}

void Input::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
	if (input) {
		input->m_window.SetWidth(static_cast<unsigned int>(width));
		input->m_window.SetHeight(static_cast<unsigned int>(height));
		glViewport(0, 0, width, height);
	}
}

void Input::SetupCallbacks() {
	glfwSetCursorPosCallback(m_window.GetHandle(), MouseCallback);
	glfwSetScrollCallback(m_window.GetHandle(), ScrollCallback);
	glfwSetFramebufferSizeCallback(m_window.GetHandle(), FramebufferSizeCallback);
}
