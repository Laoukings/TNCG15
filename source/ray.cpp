#include "ray.h"
	
	//default constructor
	ray::ray(glm::vec3 originpoint, glm::vec3 direction, glm::vec3 raycolor, ray* previousray, ray* nextray)
	: origin(originpoint), dir(direction), color(raycolor), previous(previousray), next(nextray) {}

	glm::vec3 ray::Raycolorcalc(int reflectionamount, Scene& scene) {
		return glm::vec3(0, 0, 0);
	}