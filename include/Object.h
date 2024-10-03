#pragma once

#include <glm.hpp>

class ray;

//Masterclass
class Object {
public:
	//check if it collides
	virtual bool collision(ray& ray, glm::vec3& intersectionpoint) = 0;

	//returns the normal
	virtual glm::vec3 Normal() = 0;

	//returns the color
	glm::vec3 getColor() {
		return color;
	}

protected:
	//variables
	glm::vec3 color = glm::vec3(0,0,0);
	
};

//subclass for spheres
class Sphere : public Object {
public:

	Sphere() = default;

	//sphere constructor
	Sphere(double& rad, glm::vec3 pos, glm::vec3 spherecolor) {
		radius = rad;
		position = pos;
		color = spherecolor;
		normal = Normal();
	}

	//sphere collision
	bool collision(ray& ray, glm::vec3& intersectionpoint) override;

	//sphere normal
	glm::vec3 Normal() override;

protected:
	//sphere variables
	double radius;
	glm::vec3 position;
	glm::vec3 normal;
};

//subclass for triangles
class Triangle : public Object {
public:
	Triangle() = default;

	//triangle constructor
	Triangle(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 trianglecolor) {
		//the corners of the triangle
		points[0] = point1;
		points[1] = point2;
		points[2] = point3;
		normal = Normal();
		color = trianglecolor;
	}

	//triangle collision
	bool collision(ray& ray, glm::vec3& intersectionpoint) override;

	//triangle normal
	glm::vec3 Normal() override;

protected:
	//triangle variable
	glm::vec3 points[3];
	glm::vec3 normal;
};