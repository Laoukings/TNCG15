#include "Light.h"

//constructor
Light::Light(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4 , glm::vec3 color) {

	//skapa en rektangel som är lampan
	position = Rectangle(point1, point2, point3, point4, color,2);
	area = glm::length(point2 - point1) * glm::length(point3 - point1);
	this->point1 = point1;
	this->point2 = point2;
	this->point3 = point3;
	this->point4 = point4;
	}

//ljusets färg
glm::vec3 Light::Color() {
	return position.getColor();
}

//ljusets normal
glm::vec3 Light::Normal() {
	return position.Normal();
}

//ljusets area
double Light::Area() {
	return area;
}

//returnerar en slumpmässig punkt på ljuset
glm::vec3 Light::Randompoint() {
	//random funktioner
	double randheight = (double) rand() / RAND_MAX;
	double randwidth = (double) rand() / RAND_MAX;
	glm::vec3 pointonlight1 = (point2 - point1) * glm::vec3(randheight, randheight, randheight);
	glm::vec3 pointonlight2 = (point3 - point1) * glm::vec3(randwidth, randwidth, randwidth);


	return point1 + pointonlight1 + pointonlight2;
}