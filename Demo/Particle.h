#pragma once

#include <glm/glm.hpp>

class Particle
{
public:
	Particle(glm::vec3* initialPosition, glm::vec4* initalColor, float lifeSpan);

	float getAge();
	float getLifeSpan();
	glm::vec3 getPosition();
	glm::vec4 getColor();
	~Particle();

private: 
	glm::vec4 _position;
	glm::vec4 _color;
	float _age;
	float _lifespan;
};

