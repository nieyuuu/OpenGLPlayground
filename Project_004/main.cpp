#include "../Common/Common.h"
#include "../Common/Shader.h"
#include "glm/gtc/matrix_transform.hpp"


float vertices[] = {
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // 右上角
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // 右下角
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // 左下角
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f   // 左上角
};

unsigned int indices[] = {
	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
};

int main()
{
	init();

	unsigned int VBO, EBO, VAO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	CShader s("vertex.vs", "fragment.fs");

	unsigned int Texture1 = generateTexture2D("../Resources/textures/awesomeface.png");
	unsigned int Texture2 = generateTexture2D("../Resources/textures/container.jpg");

	while (!glfwWindowShouldClose(sWindow))
	{
		processInput(sWindow);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		s.active();

		glBindVertexArray(VAO);
		s.setTexture2DUniformValue("Texture1", Texture1, 0);
		s.setTexture2DUniformValue("Texture2", Texture2, 1);

		glm::mat4 Trans(1.0f);
		Trans = glm::translate(Trans, glm::vec3(0.5f, 0.5f, 0.0f));
		Trans = glm::rotate(Trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		Trans = glm::scale(Trans, glm::vec3(0.5f, 0.5f, 1.0f));

		s.setMat4UniformValue("TranslateMat", Trans);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(sWindow);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);

	glDeleteTextures(1, &Texture1);
	glDeleteTextures(1, &Texture2);

	destroy();
}