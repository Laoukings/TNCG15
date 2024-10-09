#include "Object.h"
#include "ray.h"



//Sphere
bool Sphere::collision(ray& ray, glm::vec3& intersectionpoint) {

	glm::vec3 SminusC = ray.originpoint() - this->position;
	double c1 = glm::dot(ray.direction(), ray.direction());
	double c2 = glm::dot(ray.direction() * glm::vec3(2.0,2.0,2.0),SminusC);
	double c3 = glm::dot(SminusC,SminusC) - pow(this->radius,2);

	double arg = pow(c2, 2) - 4 * c1 * c3;

	if (arg > 0.0) {
		return true;
	}

	return false;
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

