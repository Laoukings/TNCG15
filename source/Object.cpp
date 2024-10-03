#include "Object.h"
#include "ray.h"


//Sphere
bool Sphere::collision(ray& ray, glm::vec3& intersectionpoint) {
	return true;
}

//return the spheres normal
glm::vec3 Sphere::Normal() {
	return glm::vec3(0, 0, 0);
}

//triangle
bool Triangle::collision(ray& ray, glm::vec3& intersectionpoint) {
	return true;
}

//return triangles normal
glm::vec3 Triangle::Normal() {
	return glm::vec3(0, 0, 0);
}

//rectangle
bool Rectangle::collision(ray& ray, glm::vec3& intersectionpoint) {
	return true;
}

//return rectangles normal
glm::vec3 Rectangle::Normal() {
	return glm::vec3(0, 0, 0);
}

