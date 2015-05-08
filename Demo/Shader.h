#pragma once
#include <GL/glew.h>
#include <GL/glfw.h>
#include <vector>
#include <string>


class Shader
{
public:
	Shader(GLuint type);
	~Shader();

	GLuint getShaderType();
	GLuint getID();
	void addSource(const std::string & source);
	void addSourceFromFile(const std::string& path);
	bool Compile();

private:
	GLuint shader_id;
	GLuint shader_type;
	std::vector<std::string> shader_source;
	std::vector<GLuint> uniforms;
};

