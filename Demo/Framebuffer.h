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
	void Bind(int target);
	void Unbind();
	void AttachTarget(unsigned int target);
	void AttachDepthTarget(unsigned int target);
	unsigned int GetTarget(int i);
	unsigned int GetDepthTarget();

private:
	unsigned int _id;
	std::vector<unsigned int> _targets;
	unsigned int _depthTarget;

};

