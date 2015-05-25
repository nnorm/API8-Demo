#include "ParticleSystem.h"


ParticleSystem::ParticleSystem(std::vector<ParticleEmitter> emitters, unsigned int maxParticles, std::string geomtryShaderSourcePath)
{
	this->_vertexShaderPass1 = new Shader(GL_VERTEX_SHADER);
	this->_vertexShaderPass2 = new Shader(GL_VERTEX_SHADER);
	this->_geometryShader = new Shader(GL_GEOMETRY_SHADER);
	this->_geometryShader->addSourceFromFile(geomtryShaderSourcePath);
	this->_fragmentShader = new Shader(GL_FRAGMENT_SHADER);
	this->_ProgramPass1 = new ShaderProgram();
	this->_ProgramPass2 = new ShaderProgram();
	this->_tfbufferA = new Buffer(TFB);
	this->_tfbufferB = new Buffer(TFB);
	this->_maxParticles = maxParticles;
	for each (ParticleEmitter e in emitters)
		for each (Particle p in e.emit(this->_maxParticles / emitters.size()))
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
