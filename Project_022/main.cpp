#include "../Common/Common.h"
#include "../Common/Shader.h"
#include "../Common/Camera.h"
#include "glm/gtc/matrix_transform.hpp"

const int ShadowMappingWidth = 4096;
const int ShadowMappingHeight = 4096;

unsigned int planeVBO = 0, planeVAO = 0;
unsigned int cubeVBO = 0, cubeVAO = 0;

const float planeVertices[] = {
	// positions            // normals         // texcoords
	 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
	-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
	-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

	 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
	-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
	 25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
};

const float cubeVertices[] = {
	// back face
	-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
	 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
	 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
	 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
	-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
	-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
	// front face
	-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
	 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
	 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
	 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
	-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
	-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
	// left face
	-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
	-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
	-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
	-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
	-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
	-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
	// right face
	 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
	 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
	 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
	 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
	 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
	 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
	// bottom face
	-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
	 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
	 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
	 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
	-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
	-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
	// top face
	-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
	 1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
	 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
	 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
	-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
	-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
};

void renderPlane()
{
	if (planeVAO == 0)
	{
		glGenBuffers(1, &planeVBO);
		glGenVertexArrays(1, &planeVAO);
		glBindVertexArray(planeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	glBindVertexArray(planeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void renderCube()
{
	if (cubeVAO == 0)
	{
		glGenBuffers(1, &cubeVBO);
		glGenVertexArrays(1, &cubeVAO);
		glBindVertexArray(cubeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	glBindVertexArray(cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void renderScene(const CShader& vShader)
{
	glm::mat4 Model = glm::mat4(1.0f);
	vShader.setMat4UniformValue("Model", Model);
	renderPlane();
	Model = glm::mat4(1.0f);
	Model = glm::translate(Model, glm::vec3(0.0f, 1.5f, 0.0));
	Model = glm::scale(Model, glm::vec3(0.5f));
	vShader.setMat4UniformValue("Model", Model);
	renderCube();
	Model = glm::mat4(1.0f);
	Model = glm::translate(Model, glm::vec3(2.0f, 0.0f, 1.0));
	Model = glm::scale(Model, glm::vec3(0.5f));
	vShader.setMat4UniformValue("Model", Model);
	renderCube();
	Model = glm::mat4(1.0f);
	Model = glm::translate(Model, glm::vec3(-1.0f, 0.0f, 2.0));
	Model = glm::rotate(Model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	Model = glm::scale(Model, glm::vec3(0.25));
	vShader.setMat4UniformValue("Model", Model);
	renderCube();
}

const glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);

int main()
{
	init();

	CShader DepthMappingShader("depth_map_vertex.vs", "depth_map_fragment.fs");
	CShader ShadingShader("blinn_phong_shading_vertex.vs", "blinn_phong_shading_fragment.fs");

	unsigned int Texture = generateTexture2D("../Resources/textures/wood.png");

	unsigned int DepthMap;
	glGenTextures(1, &DepthMap);
	glBindTexture(GL_TEXTURE_2D, DepthMap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float BorderColor[] = { 1.0f,1.0f,1.0f,1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, BorderColor);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, ShadowMappingWidth, ShadowMappingHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

	unsigned int DepthMappingFBO;
	glGenFramebuffers(1, &DepthMappingFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, DepthMappingFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, DepthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glBindTexture(GL_TEXTURE_2D, 0);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(sWindow))
	{
		updateTime();
		processInput(sWindow);

		//render depth map
		glBindFramebuffer(GL_FRAMEBUFFER, DepthMappingFBO);
		glClear(GL_DEPTH_BUFFER_BIT);

		glm::mat4 LightView = glm::mat4(1.0f), LightProjection = glm::mat4(1.0f);
		LightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		LightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);

		DepthMappingShader.active();
		DepthMappingShader.setMat4UniformValue("LightSpaceMatrix", LightProjection * LightView);

		glViewport(0, 0, ShadowMappingWidth, ShadowMappingHeight);
		renderScene(DepthMappingShader);
		glViewport(0, 0, WindowWidth, WindowHeight);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		//shading
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 View = glm::mat4(1.0f), Projection = glm::mat4(1.0f);
		View = sCamera.GetViewMatrix();
		Projection = glm::perspective(sCamera.Zoom, (float)WindowWidth / (float)WindowHeight, 0.1f, 100.0f);
		
		ShadingShader.active();
		ShadingShader.setMat4UniformValue("View", View);
		ShadingShader.setMat4UniformValue("Projection", Projection);
		ShadingShader.setFloatUniformValue("Shiness", 64.0f);
		ShadingShader.setFloatUniformValue("LightColor", 0.3f, 0.3f, 0.3f);
		ShadingShader.setFloatUniformValue("wsLightPos", lightPos.x, lightPos.y, lightPos.z);
		ShadingShader.setFloatUniformValue("wsCameraPos", sCamera.Position.x, sCamera.Position.y, sCamera.Position.z);
		ShadingShader.setMat4UniformValue("LightSpaceMatrix", LightProjection * LightView);
		ShadingShader.setTexture2DUniformValue("Texture", Texture, 0);
		ShadingShader.setTexture2DUniformValue("DepthMap", DepthMap, 1);

		renderScene(ShadingShader);

		glfwSwapBuffers(sWindow);
		glfwPollEvents();
	}

	destroy();

	return 0;
}