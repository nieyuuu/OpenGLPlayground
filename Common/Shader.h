#pragma once
#include <string>
#include <glm/glm.hpp>

class CShader
{
public:
	CShader(const std::string& vVertex, const std::string& vFragment, const std::string& vGeometry = "");

	void active()const;
	unsigned int programID()const;

	void setTexture2DUniformValue(const std::string& vUniformName, unsigned int vTextureID, unsigned int vBindingPoint) const;

	void setMat4UniformValue(const std::string& vUniformName, const glm::mat4& vValue) const;

	void setIntUniformValue(const std::string& vUniformName, int v0) const;
	void setIntUniformValue(const std::string& vUniformName, int v0, int v1) const;
	void setIntUniformValue(const std::string& vUniformName, int v0, int v1, int v2) const;
	void setIntUniformValue(const std::string& vUniformName, int v0, int v1, int v2, int v3) const;

	void setFloatUniformValue(const std::string& vUniformName, float v0) const;
	void setFloatUniformValue(const std::string& vUniformName, float v0, float v1) const;
	void setFloatUniformValue(const std::string& vUniformName, float v0, float v1, float v2) const;
	void setFloatUniformValue(const std::string& vUniformName, float v0, float v1, float v2, float v3) const;

private:
	unsigned int m_ProgramID = 0;

	std::string __readShaderCode(const std::string& vShader);
	void __checkCompileErrors(unsigned int vShader, const std::string& vType);
	unsigned int __createOpenGLShader(const char* vCode, unsigned int vShaderType, const std::string& vHint);
};