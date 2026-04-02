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

	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	glm::vec3 pointLightColors[] = {
		glm::vec3(1.0f, 0.6f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 1.0, 0.0),
		glm::vec3(0.2f, 0.2f, 1.0f)
	};

	// block to ensure release of resources before terminating the glfw context
	{
		Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;

		Input input(window, camera);
		input.SetupCallbacks();

		VertexBuffer vbo(vertices, sizeof(vertices));

		VertexBufferLayout layout;
		layout.push<float>(3);
		layout.push<float>(3);
		layout.push<float>(2);

		VertexArray vao;
		vao.AddBuffer(vbo, layout);

		VertexArray lightVAO;
		lightVAO.AddBuffer(vbo, layout);

		Shader lightingShader("res/color.vs", "res/color.fs");
		Shader lightCubeShader("res/light_cube.vs", "res/light_cube.fs");

		Texture containerTexture("textures/container2.png");
		Texture containerSpecularTexture("textures/container2_specular.png");

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		while (window.isClosed()) {
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			input.ProcessKeyboard(deltaTime);

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//lightingShader.use();
			//lightingShader.setInt("material.diffuse", 0);
			//containerTexture.Bind(0);
			//lightingShader.setInt("material.specular", 1);
			//containerSpecularTexture.Bind(1);
			//lightingShader.setVec3("light.position", camera.Position);
			//lightingShader.setVec3("light.direction", camera.Front);
			//lightingShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
			//lightingShader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
			//lightingShader.setVec3("viewPos", camera.Position);

			//lightingShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
			//lightingShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
			//lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
			//lightingShader.setFloat("light.constant", 1.0f);
			//lightingShader.setFloat("light.linear", 0.09f);
			//lightingShader.setFloat("light.quadratic", 0.032f);

			//lightingShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
			//lightingShader.setFloat("material.shininess", 64.0f);

			//lightingShader.setFloat("pointLights[0].constant", 1.0f);

			lightingShader.use();
			lightingShader.setInt("material.diffuse", 0);
			containerTexture.Bind(0);
			lightingShader.setInt("material.specular", 1);
			containerSpecularTexture.Bind(1);
			lightingShader.setFloat("material.shininess", 64.0f);

			// directional light
			lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
			lightingShader.setVec3("dirLight.ambient", 0.3f, 0.24f, 0.14f);
			lightingShader.setVec3("dirLight.diffuse", 0.7f, 0.42f, 0.26f);
			lightingShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

			// point lights
			for (int i = 0; i < 4; i++) {
				std::string base = "pointLights[" + std::to_string(i) + "].";
				lightingShader.setVec3(base + "position", pointLightPositions[i]);
				lightingShader.setVec3(base + "ambient", pointLightColors[i] * 0.1f);
				lightingShader.setVec3(base + "diffuse", pointLightColors[i]);
				lightingShader.setVec3(base + "specular", pointLightColors[i]);
				lightingShader.setFloat(base + "constant", 1.0f);
				lightingShader.setFloat(base + "linear", 0.09f);
				lightingShader.setFloat(base + "quadratic", 0.032f);
			}

			// spotlight
			lightingShader.setVec3("spotLight.position", camera.Position);
			lightingShader.setVec3("spotLight.direction", camera.Front);
			lightingShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
			lightingShader.setVec3("spotLight.diffuse", 0.8f, 0.8f, 0.0f);
			lightingShader.setVec3("spotLight.specular", 0.8f, 0.8f, 0.0f);
			lightingShader.setFloat("spotLight.constant", 1.0f);
			lightingShader.setFloat("spotLight.linear", 0.09f);
			lightingShader.setFloat("spotLight.quadratic", 0.032f);
			lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
			lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(13.0f)));

			lightingShader.setVec3("viewPos", camera.Position);

			glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			glm::mat4 view = camera.GetViewMatrix();
			lightingShader.setMat4("projection", projection);
			lightingShader.setMat4("view", view);
			
			vao.Bind();

			glm::mat4 model = glm::mat4(1.0f);
			lightingShader.setMat4("model", model);

			for(unsigned int i = 0; i < 10; i++)
			{
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, cubePositions[i]);
				float angle = 20.0f * i;
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				lightingShader.setMat4("model", model);

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

			//lightCubeShader.use();
			//lightCubeShader.setMat4("projection", projection);
			//lightCubeShader.setMat4("view", view);
			//model = glm::mat4(1.0f);
			//model = glm::translate(model, lightPos);
			//model = glm::scale(model, glm::vec3(0.2f));
			//lightCubeShader.setMat4("model", model);

			//lightVAO.Bind();
			//glDrawArrays(GL_TRIANGLES, 0, 36);

			glfwSwapBuffers(window.GetHandle());
			glfwPollEvents();
		}
	}
	return 0;
}