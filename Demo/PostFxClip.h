#pragma once
#include "Common.h"

#include "ShaderProgram.h"
#include "Framebuffer.h"
#include "Uniform.h"

class PostFxClip
{
public:
	PostFxClip(Shader* fragmentShader, std::vector<Uniform> uniformList);
	void toggle();
	void untoggle();
	~PostFxClip();
private: 
	Framebuffer* _fboInput;
	Framebuffer* _fboOutput;
	Shader* _vtxShader;
	ShaderProgram* _program;
	std::vector<Uniform>* _uniforms;
	const char* _vtxSource;
};