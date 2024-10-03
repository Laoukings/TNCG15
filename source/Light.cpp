#include "Light.h"

Light::Light(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 color) {

	position = Triangle(point1, point2, point3, color);

	}

glm::vec3 Light::Color() {
	return color;
}

glm::vec3 Light::Normal() {
	return glm::vec3(0,0,-1);
}