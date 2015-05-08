#pragma once
#include "Common.h"

#include "ShaderProgram.h"
#include "Buffer.h"
#include "Uniform.h"

class PostFxClip
{
public:
	PostFxClip(Shader* fragmentShader, std::vector<Uniform> uniformList);
	void toggle();
	void untoggle();
	~PostFxClip();
private: 
	Buffer* _fboInput;
	Buffer* _fboOutput;
	Shader* _vtxShader;
	ShaderProgram* _program;
	std::vector<Uniform>* _uniforms;
	const char* _vtxSource;
};