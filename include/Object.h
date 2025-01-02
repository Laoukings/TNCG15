#pragma once

#include <glm.hpp>
#include <Memory>

//så vi kan använda ray
class ray;

//master klass
class Object {
public:

	//funktioner
	virtual bool collision(ray& ray, glm::vec3& intersectionpoint) = 0;
	virtual glm::vec3 Normal() = 0;

	glm::vec3 getColor() {
		return color;
	}

	int getMaterial() {
		return material;
	}

	//variabler
protected:
	glm::vec3 color = glm::vec3(0,0,0);

	//0 = diffuse, 1 = mirror, 2 = light, 3 = room
	int material = 0;
};

//subklass för sfärer
class Sphere : public Object {
public:

	Sphere() = default;

	//sfär konstruktor
	Sphere(const double& rad, glm::vec3& pos, glm::vec3& spherecolor, int inmaterial) {
		radius = rad;
		position = pos;
		color = spherecolor;
		normal = Normal();
		material = inmaterial;
	}

	//sfär formler

	bool collision(ray& ray, glm::vec3& intersectionpoint) override;

	glm::vec3 Normal() override;

protected:
	//sfär variabler
	double radius;
	glm::vec3 position;
	glm::vec3 normal = glm::vec3(0.0,0.0,0.0);
};

//subklass för trianglar
class Triangle : public Object {
public:
	Triangle() = default;

	//triangle konstruktor
	Triangle(glm::vec3& point1, glm::vec3& point2, glm::vec3& point3, glm::vec3 trianglecolor, int inmaterial) {
		points[0] = point1;
		points[1] = point2;
		points[2] = point3;
		normal = Normal();
		color = trianglecolor;
		material = inmaterial;
	}

	//triangel formler

	bool collision(ray& ray, glm::vec3& intersectionpoint) override;

	glm::vec3 Normal() override;

	//triangel variabler
protected:

	glm::vec3 points[3];
	glm::vec3 normal;
};

class Rectangle : public Object {
public:
	Rectangle() = default;

	//rektangle konstruktor
	Rectangle(glm::vec3& point1, glm::vec3& point2, glm::vec3& point3,glm::vec3& point4, glm::vec3& rectanglecolor, int inmaterial) {
		points[0] = point1;
		points[1] = point2;
		points[2] = point3;
		points[3] = point4;
		normal = Normal();
		color = rectanglecolor;
		material = inmaterial;
	}

	//rektangel funktioner

	bool collision(ray& ray, glm::vec3& intersectionpoint) override;

	glm::vec3 Normal() override;

	//rektangel variabler
protected:
	glm::vec3 points[4];
	glm::vec3 normal;
};