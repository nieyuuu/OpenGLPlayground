#include "../Common/Common.h"
#include "../Common/Model.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../Common/Camera.h"


int main()
{
	init();

	CModel m("../Resources/objects/nanosuit/nanosuit.obj");

	CShader s("vertex.vs", "fragment.fs");

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(sWindow))
	{
		updateTime();
		processInput(sWindow);

		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		s.active();
		glm::mat4 Projection = glm::perspective(glm::radians(sCamera.Zoom), (float)WindowWidth / (float)WindowHeight, 0.1f, 100.0f);
		glm::mat4 View = sCamera.GetViewMatrix();
		s.setMat4UniformValue("Projection", Projection);
		s.setMat4UniformValue("View", View);

		glm::mat4 Model = glm::mat4(1.0f);
		Model = glm::translate(Model, glm::vec3(0.0f, -1.75f, 0.0f));
		Model = glm::scale(Model, glm::vec3(0.2f, 0.2f, 0.2f));
		s.setMat4UniformValue("Model", Model);

		m.Draw(s);

		glfwSwapBuffers(sWindow);
		glfwPollEvents();
	}

	destroy();

	return 0;
}