#pragma once

#include <stdlib.h>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include <glm/glm.hpp>

#include "Buffer.h"

using std::string;
using std::vector;

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