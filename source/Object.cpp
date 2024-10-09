#include "Object.h"
#include "ray.h"



//Sphere
bool Sphere::intersecNormal(ray& ray) {
	return false;
}

//sphere collision
bool Sphere::collision(ray& ray, glm::vec3& intersectionpoint) {

	//formula
	glm::vec3 SminusC = ray.originpoint() - this->position;
	double c1 = glm::dot(ray.direction(), ray.direction());
	double c2 = glm::dot(ray.direction() * glm::vec3(2.0, 2.0, 2.0), SminusC);
	double c3 = glm::dot(SminusC, SminusC) - pow(this->radius, 2);

	double arg = pow(c2, 2) - 4 * c1 * c3;

	//not done yet only checks if any collision not if the collision happens once or twice
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
bool Triangle::intersecNormal(ray& ray) {

	//check if normal is positive
	if (glm::dot(normal, ray.direction()) < 0)
	{
		return true;
	}
	else {
		return false;
	}
}

//triangle collision
bool Triangle::collision(ray& ray, glm::vec3& intersectionpoint) {

	//t is the distance between the point and the intersec
	double t = glm::dot((points[0] - ray.originpoint()), normal) / glm::dot(ray.direction(), normal);

	//if small it intersects same thing twice
	if (t < 0.001)
	{
		return false;
	}

	//edges
	glm::vec3 c1 = points[1] - points[0];
	glm::vec3 c2 = points[2] - points[0];

	//formula
	if (intersecNormal(ray)) {
		intersectionpoint.x = ray.originpoint().x + (t * ray.direction().x);
		intersectionpoint.y = ray.originpoint().y + (t * ray.direction().y);
		intersectionpoint.z = ray.originpoint().z + (t * ray.direction().z);
		double a = glm::dot((intersectionpoint - points[0]), c1) / glm::dot(c1, c1);
		double b = glm::dot((intersectionpoint - points[0]), c2) / glm::dot(c2, c2);

		//check collision
		if (((0.0 <= a && a <= 1.0 && 0.0 <= b && b <= 1.0) || (abs(a) <= 0.001 && 0.0 <= b && b <= 1.0) || (abs(b) <= 0.001 && 0.0 <= a && a <= 1.0)) && a + b <= 1)
		{
			intersectionpoint += (normal * glm::vec3(0.001, 0.001, 0.001));
			return true;
		}
	}

	return false;
}

//return triangles normal
glm::vec3 Triangle::Normal() {
	glm::vec3 edge0to1 = points[1] - points[0];
	glm::vec3 edge0to2 = points[2] - points[0];

	return glm::normalize(glm::cross(edge0to1, edge0to2));
}

//rectangle
bool Rectangle::intersecNormal(ray& ray) {

	//check if dot of ray and normal is positive
	if (glm::dot(normal, ray.direction()) < 0)
	{
		return true;
	}
	else {
		return false;
	}
}

// same as triangle collision without a + b < 1
bool Rectangle::collision(ray& ray, glm::vec3& intersectionpoint) {

	double t = glm::dot((points[0] - ray.originpoint()), normal) / glm::dot(ray.direction(), normal);

	if (t < 0.001)
	{
		return false;
	}

	glm::vec3 c1 = points[1] - points[0];
	glm::vec3 c2 = points[2] - points[0];

	if (intersecNormal(ray)) {
		intersectionpoint.x = ray.originpoint().x + (t * ray.direction().x);
		intersectionpoint.y = ray.originpoint().y + (t * ray.direction().y);
		intersectionpoint.z = ray.originpoint().z + (t * ray.direction().z);
		double a = glm::dot((intersectionpoint - points[0]), c1) / glm::dot(c1, c1);
		double b = glm::dot((intersectionpoint - points[0]), c2) / glm::dot(c2, c2);

		if ((0.0 <= a && a <= 1.0 && 0.0 <= b && b <= 1.0) || (abs(a) <= 0.001 && 0.0 <= b && b <= 1.0) || (abs(b) <= 0.001 && 0.0 <= a && a <= 1.0))
		{
			intersectionpoint += (normal * glm::vec3(0.001, 0.001, 0.001));
			return true;
		}
	}

	return false;
}

//return rectangles normal
glm::vec3 Rectangle::Normal() {
	glm::vec3 edge0to1 = points[1] - points[0];
	glm::vec3 edge0to2 = points[2] - points[0];

	return glm::normalize(glm::cross(edge0to1, edge0to2));
}