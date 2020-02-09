#include "../Common/Common.h"

int main()
{
	init();

	while (!glfwWindowShouldClose(sWindow))
	{
		processInput(sWindow);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(sWindow);
		glfwPollEvents();
	}

	destroy();

	return 0;
}