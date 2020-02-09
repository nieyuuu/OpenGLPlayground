#include "../Common/Common.h"
#include "../Common/Shader.h"
#include "glm/gtc/matrix_transform.hpp"

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

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(LightVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	CShader CubeShader("cube_vertex.vs", "cube_fragment.fs");
	CShader LightShader("light_vertex.vs", "light_fragment.fs");

	unsigned int DiffuseTexture = generateTexture2D("../Resources/textures/container2.png");
	unsigned int SpecularTexture = generateTexture2D("../Resources/textures/container2_specular.png");

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(sWindow))
	{
		updateTime();
		processInput(sWindow);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		CubeShader.active();
		CubeShader.setTexture2DUniformValue("m.Diffuse", DiffuseTexture, 0);
		CubeShader.setTexture2DUniformValue("m.Specular", SpecularTexture, 1);
		CubeShader.setFloatUniformValue("m.Shiness", 32);
		CubeShader.setFloatUniformValue("l.Ambient", 0.2f, 0.2f, 0.2f);
		CubeShader.setFloatUniformValue("l.Diffuse", 0.5f, 0.5f, 0.5f);
		CubeShader.setFloatUniformValue("l.Specular", 1.0f, 1.0f, 1.0f);
		CubeShader.setFloatUniformValue("l.Constant", 1.0f);
		CubeShader.setFloatUniformValue("l.Linear", 0.09f);
		CubeShader.setFloatUniformValue("l.Quadratic", 0.032f);
		CubeShader.setFloatUniformValue("l.wsPos", lightPos.x, lightPos.y, lightPos.z);
		CubeShader.setFloatUniformValue("wsCameraPos", sCamera.Position.x, sCamera.Position.y, sCamera.Position.z);

		glm::mat4 View = sCamera.GetViewMatrix();
		glm::mat4 Projection = glm::perspective(sCamera.Zoom, (float)WindowWidth / (float)WindowHeight, 0.1f, 100.0f);
		CubeShader.setMat4UniformValue("View", View);
		CubeShader.setMat4UniformValue("Projection", Projection);


		glm::mat4 Model = glm::mat4(1.0f);

		glBindVertexArray(CubeVAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			Model = glm::mat4(1.0f);
			Model = glm::translate(Model, cubePositions[i]);
			float angle = 20.0f * i;
			Model = glm::rotate(Model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			CubeShader.setMat4UniformValue("Model", Model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

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
	glDeleteTextures(1, &DiffuseTexture);
	glDeleteTextures(1, &SpecularTexture);

	destroy();

	return 0;
}