#include "Uniform.h"

Uniform::Uniform(string name, unsigned int program)
{
	this->_name = name;
	this->_location = glGetUniformLocation(program, name.c_str());
}

Uniform::~Uniform()
{
}

GLuint Uniform::getLocation()
{

	return this->_location;
}

string Uniform::getName()
{
	return this->_name;
}