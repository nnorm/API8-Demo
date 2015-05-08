#pragma once
#include "Common.h"

#include "Buffer.h"

class Model
{
public:
	Model::Model(const string& path);
	~Model();
	
	vector<unsigned int> indices;
	vector<float> vertices;
	vector<float> normals;
	vector<float> texcoords;

	void feedBuffers(Buffer* positionBuffer, Buffer* normalBuffer, Buffer* indexBuffer);

private:
	FILE * fileHandler_;
};