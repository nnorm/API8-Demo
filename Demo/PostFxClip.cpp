#include "PostFxClip.h"


PostFxClip::PostFxClip(Shader* fragmentShader, std::vector<Uniform> uniformList)
{
	this->_vtxSource = "in vec3 attrVertexPosition;"
		"in vec3 attrVertexNormal;"
		"varying vec4 v_pos;"
		"void main(void) { "
		"	gl_Position = attrVertexPosition;"
		"	v_pos = gl_Position.xyz;"
		"}";
	this->_vtxShader = new Shader(GL_VERTEX_SHADER);
	this->_vtxShader->addSource(this->_vtxSource);
	this->_vtxShader->Compile();
	this->_program = new ShaderProgram();
	this->_program->Attach(_vtxShader);
	fragmentShader->Compile();
	this->_program->Attach(fragmentShader);
	this->_program->Link();
	this->_uniforms = &uniformList;
	for each (Uniform u in *this->_uniforms)
	{
		this->_program->AddUniform(&u);
	}
}

void PostFxClip::toggle()
{
	this->_program->Use();
}

void PostFxClip::untoggle()
{
	this->_program->Unuse();
}

PostFxClip::~PostFxClip()
{
	this->_program->DeleteAllUniforms();
	this->_program->DetachAll();
	this->_program->~ShaderProgram();
	this->_vtxShader->~Shader();
}
