#pragma once
#include "Common.h"

class Shader;
class Uniform;

class ShaderProgram
{
public:
	ShaderProgram();

	void Attach(Shader* shader);
	void Detach(Shader* shader);
	void DetachAll();
	bool Link();
	void Use();
	void Unuse();
	GLuint getUniformLocation(string name);
	void AddUniform(Uniform* uniform);
	void DeleteUniform(Uniform* uniform);
	void DeleteAllUniforms();
	unsigned int getProgramID();

	~ShaderProgram();

private:
	unsigned int _programId;
	vector<Shader*> _shaders;
	vector<Uniform*> _uniforms;
};