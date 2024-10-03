#pragma once
#include <glm.hpp>
#include "Object.h"

class Light
{
public:
	Light(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 color );

	glm::vec3 Color();
	glm::vec3 Normal();

	Triangle position;

; private:
	glm::vec3 point1;
	glm::vec3 point2;
	glm::vec3 point3;
	glm::vec3 color;
};

