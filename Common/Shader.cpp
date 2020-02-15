#include "Shader.h"
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

CShader::CShader(const std::string & vVertex, const std::string & vFragment, const std::string & vGeometry)
{
	std::string VertexCode = __readShaderCode(vVertex);
	std::string FragmentCode = __readShaderCode(vFragment);
	std::string GeometryCode;

	const char* pVertex = VertexCode.c_str();
	const char* pFragment = FragmentCode.c_str();
	const char* pGeometry = nullptr;

	unsigned int Vertex = 0, Fragment = 0, Geometry = 0;

	Vertex = __createOpenGLShader(pVertex, GL_VERTEX_SHADER, "VERTEX");
	Fragment = __createOpenGLShader(pFragment, GL_FRAGMENT_SHADER, "FRAGMENT");

	if (vGeometry.size() > 0)
	{
		GeometryCode = __readShaderCode(vGeometry);
		pGeometry = GeometryCode.c_str();
		Geometry = __createOpenGLShader(pGeometry, GL_GEOMETRY_SHADER, "GEOMETRY");
	}

	m_ProgramID = glCreateProgram();
	_ASSERT(m_ProgramID);

	glAttachShader(m_ProgramID, Vertex);
	glAttachShader(m_ProgramID, Fragment);
	if (Geometry)
	{
		glAttachShader(m_ProgramID, Geometry);
	}

	glLinkProgram(m_ProgramID);
	__checkCompileErrors(m_ProgramID, "PROGRAM");

	glDeleteShader(Vertex);
	glDeleteShader(Fragment);
	if (Geometry)
	{
		glDeleteShader(Geometry);
	}
}

void CShader::active() const
{
	_ASSERT(m_ProgramID);
	glUseProgram(m_ProgramID);
}

unsigned int CShader::programID() const
{
	return m_ProgramID;
}

void CShader::setTexture2DUniformValue(const std::string& vUniformName, unsigned int vTextureID, unsigned int vBindingPoint) const
{
	_ASSERT(m_ProgramID);
	glActiveTexture(GL_TEXTURE0 + vBindingPoint);//◊¢“‚£∫œ»active£¨‘Ÿbind
	glBindTexture(GL_TEXTURE_2D, vTextureID);
	int Location = glGetUniformLocation(m_ProgramID, vUniformName.c_str());
	glUniform1i(Location, vBindingPoint);
}

void CShader::setMat4UniformValue(const std::string& vUniformName, const glm::mat4& vValue) const
{
	_ASSERT(m_ProgramID);
	int Location = glGetUniformLocation(m_ProgramID, vUniformName.c_str());
	glUniformMatrix4fv(Location, 1, false, glm::value_ptr(vValue));
}

void CShader::setIntUniformValue(const std::string& vUniformName, int v0) const
{
	_ASSERT(m_ProgramID);
	int Location = glGetUniformLocation(m_ProgramID, vUniformName.c_str());
	glUniform1i(Location, v0);
}

void CShader::setIntUniformValue(const std::string& vUniformName, int v0, int v1) const
{
	_ASSERT(m_ProgramID);
	int Location = glGetUniformLocation(m_ProgramID, vUniformName.c_str());
	glUniform2i(Location, v0, v1);
}

void CShader::setIntUniformValue(const std::string& vUniformName, int v0, int v1, int v2) const
{
	_ASSERT(m_ProgramID);
	int Location = glGetUniformLocation(m_ProgramID, vUniformName.c_str());
	glUniform3i(Location, v0, v1, v2);
}

void CShader::setIntUniformValue(const std::string& vUniformName, int v0, int v1, int v2, int v3) const
{
	_ASSERT(m_ProgramID);
	int Location = glGetUniformLocation(m_ProgramID, vUniformName.c_str());
	glUniform4i(Location, v0, v1, v2, v3);
}

void CShader::setFloatUniformValue(const std::string& vUniformName, float v0) const
{
	_ASSERT(m_ProgramID);
	int Location = glGetUniformLocation(m_ProgramID, vUniformName.c_str());
	glUniform1f(Location, v0);
}

void CShader::setFloatUniformValue(const std::string& vUniformName, float v0, float v1) const
{
	_ASSERT(m_ProgramID);
	int Location = glGetUniformLocation(m_ProgramID, vUniformName.c_str());
	glUniform2f(Location, v0, v1);
}

void CShader::setFloatUniformValue(const std::string& vUniformName, float v0, float v1, float v2) const
{
	_ASSERT(m_ProgramID);
	int Location = glGetUniformLocation(m_ProgramID, vUniformName.c_str());
	glUniform3f(Location, v0, v1, v2);
}

void CShader::setFloatUniformValue(const std::string& vUniformName, float v0, float v1, float v2, float v3) const
{
	_ASSERT(m_ProgramID);
	int Location = glGetUniformLocation(m_ProgramID, vUniformName.c_str());
	glUniform4f(Location, v0, v1, v2, v3);
}

std::string CShader::__readShaderCode(const std::string& vShader)
{
	std::string ShaderCode;
	std::ifstream ShaderFile;
	std::stringstream StringStream;

	ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		ShaderFile.open(vShader);
		StringStream << ShaderFile.rdbuf();
		ShaderFile.close();

		ShaderCode = StringStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ::" << vShader << std::endl;
	}

	return ShaderCode;
}

void CShader::__checkCompileErrors(unsigned int vShader, const std::string& vType)
{
	int Success = 0;
	char Info[1024];

	if (vType != "PROGRAM")
	{
		glGetShaderiv(vShader, GL_COMPILE_STATUS, &Success);
		if (!Success)
		{
			glGetShaderInfoLog(vShader, 1024, nullptr, Info);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << vType << "\n" << Info << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(vShader, GL_LINK_STATUS, &Success);
		if (!Success)
		{
			glGetProgramInfoLog(vShader, 1024, NULL, Info);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << vType << "\n" << Info << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

unsigned int CShader::__createOpenGLShader(const char* vCode, unsigned int vShaderType, const std::string& vHint)
{
	unsigned int Shader = glCreateShader(vShaderType);
	glShaderSource(Shader, 1, &vCode, nullptr);
	glCompileShader(Shader);
	__checkCompileErrors(Shader, vHint);

	return Shader;
}
