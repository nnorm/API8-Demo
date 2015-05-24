#include "ParticleSystem.h"


ParticleSystem::ParticleSystem(string geometryShaderSource)
{
	this->_vertexShaderPass1 = new Shader(GL_VERTEX_SHADER);
	this->_vertexShaderPass2 = new Shader(GL_VERTEX_SHADER);
	this->_geometryShader = new Shader(GL_GEOMETRY_SHADER);
	this->_fragmentShader = new Shader(GL_FRAGMENT_SHADER);
	this->_ProgramPass1 = new ShaderProgram();
	this->_ProgramPass2 = new ShaderProgram();
	this->_tfbufferA = new Buffer(TFB);
	this->_tfbufferB = new Buffer(TFB);

	for each (ParticleEmitter e in this->_emitters)
		for each (Particle p in e.emit(_maxParticles / this->_emitters.size()))
			this->_particles.push_back(p);
}

void ParticleSystem::update(double dt)
{

}

void ParticleSystem::render(glm::mat4* viewMat, glm::mat4* projMat)
{

}

ParticleSystem::~ParticleSystem()
{
}
