#include "ShaderProgram.h"

#include "Shader.h"
#include "Uniform.h"

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
	Shader* p;
	for(int i=0; i < this->_shaders.size(); i++)
		if(this->_shaders[i]==shader)
			p = this->_shaders[i];	
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
	for(int i = 0; i < this->_uniforms.size(); i++)
	{
		if(this->_uniforms[i] != this->_uniforms[this->_uniforms.size()-1])
		{
			std::cout << "[GL] Uniform successfully added : " << uniform->getName().c_str() << std::endl;	
			break;
		}
	}	
#endif 
}

void ShaderProgram::DeleteUniform(Uniform* uniform)
{
	for(int i = 0; i < this->_uniforms.size(); i++)
	{
		if(this->_uniforms[i] != this->_uniforms[this->_uniforms.size()-1])
		{
			this->_uniforms.erase(this->_uniforms[i]);
			break;
		}
	}
}

void ShaderProgram::DeleteAllUniforms()
{
	this->_uniforms.clear();
}

unsigned int ShaderProgram::getProgramID()
{
	return this->_programId;
}
