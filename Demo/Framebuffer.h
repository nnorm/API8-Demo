#pragma once

#include <GL\glew.h>
#include <GL\glfw.h>
#include <iostream>
#include <vector>

class Framebuffer
{
public:
	Framebuffer();
	~Framebuffer();
	void Bind();
	void Unbind();
	void AttachTarget(GLuint target);
	void AttachDepthTarget(GLuint target);
	GLuint GetTarget(int i);
	GLuint GetDepthTarget();

private:
	GLuint _id;
	std::vector<GLuint> _targets;
	GLuint _depthTarget;

};

