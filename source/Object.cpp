#include "Object.h"
#include "ray.h"


//Sphere
bool Sphere::collision(ray& ray, intersectionpoint) {
	return true;
}

glm::vec3 Sphere::Normal() {
	return glm::vec3(0, 0, 0);
}

//triangle
bool Triangle::collision(ray& ray, intersectionpoint) {
	return true;
}

glm::vec3 Triangle::Normal() {
	return glm::vec3(0, 0, 0);
}
