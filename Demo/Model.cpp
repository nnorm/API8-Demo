#include "Model.h"

/***************************************************************************/
/* Loading routing made by xtrium/LNX. Taken with permission from DKEngine */
/***************************************************************************/

Model::Model(const string& path)
{
	std::vector<float> unsorted_vertices;
	std::vector<float> unsorted_normals;
	std::vector<float> unsorted_texcoords;

	std::vector< std::tuple<uint32_t, uint32_t, uint32_t> > faceHashes;

	std::ifstream infile(path, std::ios::in | std::ios::binary);
	std::string line;
	while (std::getline(infile, line))
	{
		if (line.size() < 2)
			continue;

		if (line[0] == '#')
			continue;

		std::vector<std::string> tokens;
		std::istringstream iss(line);
		std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(tokens));

		if (tokens[0] == "v")
		{ // vertex
			unsorted_vertices.push_back(::atof(tokens[1].c_str()));
			unsorted_vertices.push_back(::atof(tokens[2].c_str()));
			unsorted_vertices.push_back(::atof(tokens[3].c_str()));
		}

		if (tokens[0] == "vn")
		{ // normal
			unsorted_normals.push_back(::atof(tokens[1].c_str()));
			unsorted_normals.push_back(::atof(tokens[2].c_str()));
			unsorted_normals.push_back(::atof(tokens[3].c_str()));
		}

		if (tokens[0] == "vt")
		{ // texture coordinate
			unsorted_texcoords.push_back(::atof(tokens[1].c_str()));
			unsorted_texcoords.push_back(::atof(tokens[2].c_str()));
		}

		if (tokens[0] == "f")
		{ // face
			if (tokens.size() > 4)
			{
				std::cout << "Mesh contains non-triangle faces, please triangulate before conversion." << std::endl;
				return;
			}

			for (uint32_t i = 1; i < tokens.size(); ++i)
			{
				std::istringstream fs(tokens[i]);
				std::string tmp;

				// Build a tuple for the current face's current vertex
				std::vector<uint32_t> fv;
				while (std::getline(fs, tmp, '/'))
				{
					if (tmp.empty())
						fv.push_back(static_cast<uint32_t>(-1));
					else
						fv.push_back(::atoi(tmp.c_str()) - 1);
				}
				if (fv.size() == 1)
				{
					fv.push_back(static_cast<uint32_t>(-1));
					fv.push_back(static_cast<uint32_t>(-1));
				}
				auto vTuple = std::make_tuple(fv[0], fv[1], fv[2]);

				// If current face tuple doesn't exist yet, add it to the list
				if (std::find(faceHashes.begin(), faceHashes.end(), vTuple) == faceHashes.end())
					faceHashes.push_back(vTuple);

				// Write index of tuple to index list
				indices.push_back(std::distance(faceHashes.begin(), std::find(faceHashes.begin(), faceHashes.end(), vTuple)));
			}
		}
	}

	// Creates sorted vertex attrib arrays for each found attribute
	for (auto fh : faceHashes)
	{
		vertices.push_back(unsorted_vertices[std::get<0>(fh) * 3 + 0]);
		vertices.push_back(unsorted_vertices[std::get<0>(fh) * 3 + 1]);
		vertices.push_back(unsorted_vertices[std::get<0>(fh) * 3 + 2]);

		if (std::get<1>(fh) != static_cast<uint32_t>(-1))
		{
			texcoords.push_back(unsorted_texcoords[std::get<1>(fh) * 2 + 0]);
			texcoords.push_back(unsorted_texcoords[std::get<1>(fh) * 2 + 1]);
		}

		if (std::get<2>(fh) != static_cast<uint32_t>(-1))
		{
			normals.push_back(unsorted_normals[std::get<2>(fh) * 3 + 0]);
			normals.push_back(unsorted_normals[std::get<2>(fh) * 3 + 1]);
			normals.push_back(unsorted_normals[std::get<2>(fh) * 3 + 2]);
		}
	}
}

Model::~Model()
{
	delete(this->fileHandler_);
}