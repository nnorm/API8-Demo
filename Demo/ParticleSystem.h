#pragma once

#include <gl/glew.h>
#include <gl/glfw.h>
#include <vector>
#include <string>

#include "Particle.h"
#include "ParticleEmitter.h"
#include "Buffer.h"
#include "Shader.h"
#include "ShaderProgram.h"

class ParticleSystem
{
public:
	ParticleSystem(std::string geomtryShaderSource);

	void update(double dt);
	void render(glm::mat4* viewMat, glm::mat4* projMat);

	~ParticleSystem();

private:
	/* Basic attributes of a particle system */
	glm::vec3 _size;
	int _maxParticles;
	std::vector < ParticleEmitter > _emitters;
	std::vector < Particle > _particles;
	/* Needed for the rendering */
	Shader* _geometryShader;
	Shader* _vertexShaderPass1;
	Shader* _vertexShaderPass2;
	Shader* _fragmentShader;
	ShaderProgram* _ProgramPass1;
	ShaderProgram* _ProgramPass2;
	/* Needed for updating particles */
	Buffer* _tfbufferA;
	Buffer* _tfbufferB;
	std::vector < std::string > varyings;
};