#include "ParticleEmitter.h"


ParticleEmitter::ParticleEmitter()
{
}

std::vector< Particle > ParticleEmitter::emit(int quantity, glm::vec4* initialColor)
{
	std::vector<Particle> particleList;
	for (int i = 0; i < quantity; i++)
	{
		glm::vec3* pos = &(glm::vec3(0.0f)+this->_position);
		glm::vec4* col = &glm::vec4(1.0f);
		Particle p(pos, initialColor, 100.0f);
		particleList.push_back(p);
	}
	return particleList;
}

ParticleEmitter::~ParticleEmitter()
{
}
