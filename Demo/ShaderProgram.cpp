#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
	this->_programId = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(this->_programId);
}

void ShaderProgram::Attach(Shader* shader)
{
	this->_shaders.push_back(shader);
	glAttachShader(this->_programId, shader->getID());
}

void ShaderProgram::Detach(Shader* shader)
{
	auto p = std::find(this->_shaders.begin(), this->_shaders.end(), shader);
	if (p != this->_shaders.end())
	{
		glDetachShader(this->_programId, shader->getID());
		this->_shaders.erase(p);
	}
}

void ShaderProgram::DetachAll()
{
	vector<Shader*> shaderList = this->_shaders;
	for (Shader* s : shaderList)
	{
		Detach(s);
	}
}

bool ShaderProgram::Link()
{
	glLinkProgram(this->_programId);

	int success = GL_FALSE;
	glGetProgramiv(this->_programId, GL_LINK_STATUS, &success);

	if (success==GL_TRUE)
	{
		DetachAll();
		return true;
	}

	GLint length = 0;
	glGetProgramiv(this->_programId, GL_INFO_LOG_LENGTH, &length);

	std::vector<GLchar> infoLog(length);
	glGetProgramInfoLog(this->_programId, length, &length, &infoLog[0]);

#ifdef _DEBUG
	std::cout << "[Shader Program] info log : " << infoLog[0] << std::endl;
#endif 

	return false;
}

void ShaderProgram::Use()
{
	glUseProgram(this->_programId);
}

void ShaderProgram::Unuse()
{
	glUseProgram(0);
}

void ShaderProgram::AddUniform(Uniform* uniform)
{
	this->_uniforms.push_back(uniform);
#ifdef _DEBUG
	if (std::find(this->_uniforms.begin(), this->_uniforms.end(), uniform) != this->_uniforms.end())
		std::cout << "[GL] Uniform successfully added : " << uniform->getName().c_str() << std::endl;
#endif 
}

void ShaderProgram::DeleteUniform(Uniform* uniform)
{
	if (std::find(this->_uniforms.begin(), this->_uniforms.end(), uniform) != this->_uniforms.end())
		this->_uniforms.erase(std::find(this->_uniforms.begin(), this->_uniforms.end(), uniform));
}

void ShaderProgram::DeleteAllUniforms()
{
	this->_uniforms.clear();
}

unsigned int ShaderProgram::getProgramID()
{
	return this->_programId;
}