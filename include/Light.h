#pragma once
#include <glm.hpp>
#include "Object.h"
#include <random>

class Light
{
public:
	//light konstruktor
	Light(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3,  glm::vec3 point4,  glm::vec3 color );

	//light funktioner
	glm::vec3 Color();
	glm::vec3 Normal();
	glm::vec3 Randompoint();
	double Area();

	//ljuskällans objekt
	Rectangle position;

; private:
	//variabler
	glm::vec3 point1;
	glm::vec3 point2;
	glm::vec3 point3;
	glm::vec3 point4;
	glm::vec3 color;
	double area;
};

