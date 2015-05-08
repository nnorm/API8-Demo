#pragma once
#include <GL/glew.h>
#include <GL/glfw.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using std::string;
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;


class Uniform
{
public:
	void operator = (bool t)		{ glUniform1i(this->_location, t ? 1 : 0); };
	void operator = (int t)			{ glUniform1i(this->_location, t); };
	void operator = (float t)		{ glUniform1f(this->_location, t); };
	void operator = (const vec2& t) { glUniform2f(this->_location, t.x, t.y); };
	void operator = (const vec3& t) { glUniform3f(this->_location, t.x, t.y, t.z); };
	void operator = (const vec4& t) { glUniform4f(this->_location, t.x, t.y, t.z, t.w); };
	void operator = (const mat4& t) { glUniformMatrix4fv(this->_location, 1, false, glm::value_ptr(t)); };

	Uniform(string name, unsigned int program);
	~Uniform();

	unsigned int getUniformLocation();
	string getName();

private:
	GLuint _location;
	string _name;
};