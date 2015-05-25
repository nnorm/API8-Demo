#include "ParticleSystem.h"


ParticleSystem::ParticleSystem(std::vector<ParticleEmitter> emitters, unsigned int maxParticles, std::string geomtryShaderSourcePath)
{
	/* shaderz */
	this->_vertexShaderPass1 = new Shader(GL_VERTEX_SHADER);
	this->_vertexShaderPass2 = new Shader(GL_VERTEX_SHADER);
	this->_geometryShader = new Shader(GL_GEOMETRY_SHADER);
	this->_geometryShader->addSourceFromFile(geomtryShaderSourcePath);
	this->_fragmentShader = new Shader(GL_FRAGMENT_SHADER);
	this->_ProgramPass1 = new ShaderProgram();
	this->_ProgramPass2 = new ShaderProgram();
	/* bufferz */
	this->_tfbufferA = new Buffer(TFB);
	this->_tfbufferB = new Buffer(TFB);
	this->_lastBufferUsed = false;
	/* particlez */
	this->_maxParticles = maxParticles;
	for each (ParticleEmitter e in emitters)
		for each (Particle p in e.emit(this->_maxParticles / emitters.size(), &glm::vec4(1.0f)))
			this->_particles.push_back(p);
	/* Next is filling the TFB A with particles infos.
	Might get rid of the _particles list attribute and do everything in the for each loop above. */
	/* The TFB varyings are going to be (GL_INTERLEAVED_ATTRIBS):
	{"PositionAndAge"(vec4), "Color"(vec4), lifeSpan(float)}*/
}

/* this is where particles gets updated */
/* 1. render particles offscreen into a tfb (either A or B) 
   2. pass the tfb datas to a geometry shader and updates those in there
   3. output updated data into the second tfb
   4. ???
   5. profit */
void ParticleSystem::update(double dt)
{
	/* Stuff that might be here */
	
	if (!this->_lastBufferUsed) /* which TFB we have to bind ? */
	{
		/* TFB A to be bound */
		/* here goes step 1 */
	}
	else
	{
		/* TFB B to be bound */
		/* here goes step 1 */
	}
	/* here goes step 2 */
	/* Have to use _size class attribute to now when a particle shall die/placed back at inital position */
	if (this->_lastBufferUsed) /* which TFB we have to bind ? */
	{
		/* TFB B to be bound */
		/* here goes step 3 */
	}
	else
	{
		/* TFB A to be bound */
		/* here goes step 3 */
	}
}

/* Here, using the scene's view matrix and projection matrix, 
   render updated particles to screen. */
void ParticleSystem::render(glm::mat4* viewMat, glm::mat4* projMat)
{
	/* choosing which buffer to get data to render */
	if (!this->_lastBufferUsed)
	{
		/* render TFB A */
		/* bind the buffer to be used as an input data for the vertex and fragment shader */
	}
	else
	{
		/* render TFB B*/
	}
	/* render actual data */
}

/* calling destructor of everything */
ParticleSystem::~ParticleSystem()
{
	this->_ProgramPass2->~ShaderProgram();
	this->_ProgramPass1->~ShaderProgram();
	this->_fragmentShader->~Shader();
	this->_vertexShaderPass2->~Shader();
	this->_vertexShaderPass1->~Shader();
	this->_geometryShader->~Shader();
	this->_tfbufferB->~Buffer();
	this->_tfbufferA->~Buffer();
}
