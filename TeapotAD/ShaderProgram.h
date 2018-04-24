#pragma once

#include "gl_core_4_3.hpp"
#include "glm.hpp"
#include <string>

class ShaderProgram
{
private:
	GLuint programId;

	GLuint LoadShader(const std::string shaderPath, GLenum type);
	void CompileShader(GLuint shaderID);

	void LinkProgram();

public:
	ShaderProgram();
	ShaderProgram(const std::string vertShaderName, const std::string fragShaderName);

	void Use();
	void Disable();
	GLuint GetProgramId();

	void setAttrib(const std::string name, const GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);

	void setUniform(const std::string name, const glm::vec2 &v);
	void setUniform(const std::string name, const glm::vec3 &v);
	void setUniform(const std::string name, const glm::vec4 &v);
	void setUniform(const std::string name, const glm::mat3 &m);
	void setUniform(const std::string name, const glm::mat4 &m);
	void setUniform(const std::string name, float val);
	void setUniform(const std::string name, int val);
	void setUniform(const std::string name, bool val);
	void setUniform(const std::string name, GLuint val);
};