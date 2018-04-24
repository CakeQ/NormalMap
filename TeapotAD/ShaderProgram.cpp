#include "ShaderProgram.h"

#include <iostream>
#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram()
{}

ShaderProgram::ShaderProgram(const std::string vertShaderPath, const std::string fragShaderPath)
{
	programId = gl::CreateProgram();

	CompileShader(LoadShader(vertShaderPath, gl::VERTEX_SHADER));
	CompileShader(LoadShader(fragShaderPath, gl::FRAGMENT_SHADER));

	LinkProgram();
}

GLuint ShaderProgram::LoadShader(const std::string shaderPath, GLenum type)
{
	GLuint shaderID = gl::CreateShader(type);

	std::ifstream file;
	file.open(shaderPath.c_str());

	if (!file.good())
	{
		std::cout << "Failed to open file: " << shaderPath << std::endl;
		exit(-1);
	}

	std::stringstream stream;
	stream << file.rdbuf();
	file.close();
	std::string source = stream.str();

	const char *sourceChars = source.c_str();

	// Associate the source with the shader id
	gl::ShaderSource(shaderID, 1, &sourceChars, NULL);

	//attach loaded shader to programID
	gl::AttachShader(programId, shaderID);

	return shaderID;
}

void ShaderProgram::CompileShader(GLuint shaderID)
{
	// Compile the shader
	gl::CompileShader(shaderID);

	// Check the compilation status and report any errors
	GLint shaderStatus;
	gl::GetShaderiv(shaderID, gl::COMPILE_STATUS, &shaderStatus);

	// If the shader failed to compile, display the info log and quit out
	if (shaderStatus == gl::FALSE_)
	{
		GLint infoLogLength;
		gl::GetShaderiv(shaderID, gl::INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		gl::GetShaderInfoLog(shaderID, infoLogLength, NULL, strInfoLog);

		std::cout << "Shader compilation failed: " << strInfoLog << std::endl;
		delete[] strInfoLog;
		exit(-1);
	}
	else
	{
		std::cout << "Shader compilation OK" << std::endl;
	}
}

void ShaderProgram::LinkProgram()
{
	// Perform the linking process
	gl::LinkProgram(this->programId);

	// Check the status
	GLint linkStatus;
	gl::GetProgramiv(this->programId, gl::LINK_STATUS, &linkStatus);
	if (linkStatus == gl::FALSE_)
	{
		std::cout << "Shader program linking failed." << std::endl;
		exit(-1);
	}
	else
	{
		std::cout << "Shader program linking OK." << std::endl;
	}
}

void ShaderProgram::Use()
{
	gl::UseProgram(this->programId);
}

void ShaderProgram::Disable()
{
	gl::UseProgram(0);
}

GLuint ShaderProgram::GetProgramId()
{
	return this->programId;
}

void ShaderProgram::setAttrib(const std::string name, const GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer)
{
	GLint loc = gl::GetAttribLocation(this->programId, name.c_str());
	gl::EnableVertexAttribArray(loc);
	gl::VertexAttribPointer(loc, size, type, normalized, stride, pointer);
}

void ShaderProgram::setUniform(const std::string name, const glm::vec2 &v)
{
	GLint loc = gl::GetUniformLocation(this->programId, name.c_str());
	gl::Uniform2f(loc, v.x, v.y);
}

void ShaderProgram::setUniform(const std::string name, const glm::vec3 &v)
{
	GLint loc = gl::GetUniformLocation(this->programId, name.c_str());
	gl::Uniform3f(loc, v.x, v.y, v.z);
}

void ShaderProgram::setUniform(const std::string name, const glm::vec4 &v)
{
	GLint loc = gl::GetUniformLocation(this->programId, name.c_str());
	gl::Uniform4f(loc, v.x, v.y, v.z, v.w);
}

void ShaderProgram::setUniform(const std::string name, const glm::mat3 &m)
{
	GLint loc = gl::GetUniformLocation(this->programId, name.c_str());
	gl::UniformMatrix3fv(loc, 1, gl::FALSE_, &m[0][0]);
}

void ShaderProgram::setUniform(const std::string name, const glm::mat4 &m)
{
	GLint loc = gl::GetUniformLocation(this->programId, name.c_str());
	gl::UniformMatrix4fv(loc, 1, gl::FALSE_, &m[0][0]);
}

void ShaderProgram::setUniform(const std::string name, float val)
{
	GLint loc = gl::GetUniformLocation(this->programId, name.c_str());
	gl::Uniform1f(loc, val);
}

void ShaderProgram::setUniform(const std::string name, int val)
{
	GLint loc = gl::GetUniformLocation(this->programId, name.c_str());
	gl::Uniform1i(loc, val);
}

void ShaderProgram::setUniform(const std::string name, bool val)
{
	GLint loc = gl::GetUniformLocation(this->programId, name.c_str());
	gl::Uniform1i(loc, val);
}

void ShaderProgram::setUniform(const std::string name, GLuint val)
{
	GLint loc = gl::GetUniformLocation(this->programId, name.c_str());
	gl::Uniform1ui(loc, val);
}
