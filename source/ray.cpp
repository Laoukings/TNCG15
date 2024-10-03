#include "ray.h"

	ray::ray(glm::vec3 originpoint, glm::vec3 direction, glm::vec3 raycolor, ray* previousray, ray* nextray)
	: origin(originpoint), dir(direction), color(raycolor), previous(previousray), next(nextray) {}

