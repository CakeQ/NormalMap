#pragma once

#include "glm.hpp"
#include <vector>
#include "gl_core_4_3.hpp"

struct Mesh
{
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<GLuint> indices;
};