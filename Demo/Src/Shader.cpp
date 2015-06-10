#include <iostream>
#include <fstream>
#include "Shader.h"

Shader::Shader(GLuint type)
{
	this->shader_type = type;

	this->shader_id = glCreateShader((GLenum)this->shader_type);
}

Shader::~Shader()
{
	glDeleteShader(this->shader_id);
}

GLuint Shader::getShaderType()
{
	return this->shader_type;
}

GLuint Shader::getID()
{
	return this->shader_id;
}

void Shader::addSource(const std::string & source)
{
	this->shader_source.push_back(source);
}

void Shader::addSourceFromFile(const std::string& path)
{
	std::ifstream file(path.c_str());

	if (!file)
	{
		std::cout << "[System] Could not load shader source file :" << path.c_str() << std::endl;
	}

	std::string line;
	std::string source;

	while (getline(file, line))
		source += line + '\n';

	file.close();

	this->shader_source.push_back(source);
}

bool Shader::Compile()
{
	bool success = false;

	const char** code = new const char*[this->shader_source.size()];
	for (unsigned int i = 0; i < this->shader_source.size(); i++)
		code[i] = this->shader_source[i].c_str();

	glShaderSource(this->shader_id, this->shader_source.size(), code, nullptr);
	glCompileShader(this->shader_id);

	int compile = false;

	glGetShaderiv(this->shader_id, GL_COMPILE_STATUS, &compile);
	success = (compile == GL_TRUE);

	if (!success)
	{
		GLint length = 0;
		glGetShaderiv(this->shader_id, GL_INFO_LOG_LENGTH, &length);
		std::vector<GLchar> infoLog(length);
		glGetShaderInfoLog(this->shader_id, length, &length, &infoLog[0]);
#ifdef _DEBUG
		std::cout << "[Shader output] Error :" << infoLog[0] << std::endl;
#endif 
	}

	delete[] code;

	return success;
}

