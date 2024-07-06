#pragma once

#include <iostream>

#include "glm/glm.hpp"

class Shader
{
private:
	std::string code;
	
public:
	glm::uint id;
	
	Shader(const char* code);
	~Shader();
};
