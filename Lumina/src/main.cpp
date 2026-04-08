#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "shader.h"
#include "Camera.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Window.h"
#include "Input.h"
#include "Model.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
	Window window(SCR_WIDTH, SCR_HEIGHT);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	// block to ensure release of resources before terminating the glfw context
	{
		Model ourModel("models/IronMan/IronMan.obj");

		Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;

		Input input(window, camera);
		input.SetupCallbacks();

		Shader lightingShader("res/color.vs", "res/color.fs");

		bool spotlightOn = true;

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		while (window.isClosed()) {
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			input.ProcessKeyboard(deltaTime);

			glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			lightingShader.use();

			glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)window.GetWidth() / (float)window.GetHeight(), 0.1f, 100.0f);
			glm::mat4 view = camera.GetViewMatrix();
			lightingShader.setMat4("projection", projection);
			lightingShader.setMat4("view", view);

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::scale(model, glm::vec3(0.1f));
			lightingShader.setMat4("model", model);

			ourModel.Draw(lightingShader);

			glfwSwapBuffers(window.GetHandle());
			glfwPollEvents();
		}
	}
	return 0;
}