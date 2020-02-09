#include "../Common/Common.h"
#include "../Common/Shader.h"
#include "glm/gtc/matrix_transform.hpp"

float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main()
{
	init();

	unsigned int VBO, CubeVAO, LightVAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &CubeVAO);
	glGenVertexArrays(1, &LightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(CubeVAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(LightVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	CShader CubeShader("cube_vertex.vs", "cube_fragment.fs");
	CShader LightShader("light_vertex.vs", "light_fragment.fs");

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(sWindow))
	{
		updateTime();
		processInput(sWindow);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		CubeShader.active();
		CubeShader.setFloatUniformValue("ObjectColor", 1.0f, 0.5f, 0.31f);
		CubeShader.setFloatUniformValue("Shiness", 32.0f);
		CubeShader.setFloatUniformValue("LightColor", 1.0f, 1.0f, 1.0f);
		CubeShader.setFloatUniformValue("wsLightPos", lightPos.x, lightPos.y, lightPos.z);
		CubeShader.setFloatUniformValue("wsCameraPos", sCamera.Position.x, sCamera.Position.y, sCamera.Position.z);

		glm::mat4 View = sCamera.GetViewMatrix();
		glm::mat4 Projection = glm::perspective(sCamera.Zoom, (float)WindowWidth / (float)WindowHeight, 0.1f, 100.0f);
		CubeShader.setMat4UniformValue("View", View);
		CubeShader.setMat4UniformValue("Projection", Projection);

		glm::mat4 Model = glm::mat4(1.0f);
		CubeShader.setMat4UniformValue("Model", Model);

		glBindVertexArray(CubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		LightShader.active();
		LightShader.setMat4UniformValue("View", View);
		LightShader.setMat4UniformValue("Projection", Projection);
		Model = glm::mat4(1.0f);
		Model = glm::translate(Model, lightPos);
		Model = glm::scale(Model, glm::vec3(0.2f, 0.2f, 0.2f));
		LightShader.setMat4UniformValue("Model", Model);

		glBindVertexArray(LightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(sWindow);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &CubeVAO);
	glDeleteVertexArrays(1, &LightVAO);

	destroy();

	return 0;
}