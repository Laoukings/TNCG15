#include "Light.h"

//constructor
Light::Light(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4 , glm::vec3 color) {

	//rectangle light
	position = Rectangle(point1, point2, point3, point4, color,2);
	area = glm::length(point2 - point1) * glm::length(point3 - point1);
	this->point1 = point1;
	}

//the color of the light
glm::vec3 Light::Color() {
	return color;
}

//the normal of the light
glm::vec3 Light::Normal() {
	//return position.Normal();
	return position.Normal();
}

double Light::Area() {
	return area;
}

//returns a random point on light
glm::vec3 Light::Randompoint() {
	double randheight = (double) rand() / RAND_MAX;
	double randwidth = (double) rand() / RAND_MAX;
	glm::vec3 pointonlight1 = (point2 - point1) * glm::vec3(randheight, randheight, randheight);
	glm::vec3 pointonlight2 = (point3 - point1) * glm::vec3(randwidth, randwidth, randwidth);


	return point1 + pointonlight1 + pointonlight2;
}