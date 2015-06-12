#pragma once

#include <GL/glew.h>
#include <GL/glfw.h>

#include <cstdlib>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <bass.h>
#include <rocket/sync.h>

template<typename T> using vector                    = std::vector<T>;
template<typename K, typename V> using map           = std::map<K, V>;
//template<typename K, typename V> using tuple         = std::tuple < K, V > ;
template<typename K, typename V> using pair          = std::pair < K, V > ;
template<typename K, typename V> using unordered_map = std::unordered_map < K, V > ;
template<typename T> using shared_ptr                = std::shared_ptr<T>;
template<typename T> using unique_ptr                = std::unique_ptr<T>;
using std::string;
using std::istream;
using std::ostream;

using glm::bvec2;
using glm::bvec3;
using glm::bvec4;
using glm::ivec2;
using glm::ivec3;
using glm::ivec4;
using glm::uvec2;
using glm::uvec3;
using glm::uvec4;
using glm::dvec2;
using glm::dvec3;
using glm::dvec4;
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat2;
using glm::mat2x3;
using glm::mat2x4;
using glm::mat3;
using glm::mat3x2;
using glm::mat3x4;
using glm::mat4;
using glm::mat4x2;
using glm::mat4x3;
using glm::dmat2;
using glm::dmat2x3;
using glm::dmat2x4;
using glm::dmat3;
using glm::dmat3x2;
using glm::dmat3x4;
using glm::dmat4;
using glm::dmat4x2;
using glm::dmat4x3;
using glm::quat;
