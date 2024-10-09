#include "Light.h"

//constructor
Light::Light(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4 , glm::vec3 color) {

	//rectangle light
	position = Rectangle(point1, point2, point3, point4, color);

	}

//the color of the light
glm::vec3 Light::Color() {
	return color;
}

//the normal of the light
glm::vec3 Light::Normal() {
	return glm::vec3(0,0,-1);
}