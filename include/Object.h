#pragma once

#include <glm.hpp>

class ray;

//Masterclass
class Object {
public:

	virtual bool intersecNormal(ray& ray) = 0;

	//check if it collides
	virtual bool collision(ray& ray, glm::vec3& intersectionpoint) = 0;

	//returns the normal
	virtual glm::vec3 Normal() = 0;

	//returns the color
	glm::vec3 getColor() {
		return color;
	}

	int getMaterial() {
		return material;
	}

protected:
	//variables
	glm::vec3 color = glm::vec3(0,0,0);

	//0 = diffuse, 1 = mirror, 2 = light, 3 = room
	int material;
};

//subclass for spheres
class Sphere : public Object {
public:

	Sphere() = default;

	//sphere constructor
	Sphere(double rad, glm::vec3 pos, glm::vec3 spherecolor, int inmaterial) {
		radius = rad;
		position = pos;
		color = spherecolor;
		normal = Normal();
		material = inmaterial;
	}

	bool intersecNormal(ray& ray) override;

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
	Triangle(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 trianglecolor, int inmaterial) {
		//the corners of the triangle
		points[0] = point1;
		points[1] = point2;
		points[2] = point3;
		normal = Normal();
		color = trianglecolor;
		material = inmaterial;
	}

	bool intersecNormal(ray& ray) override;

	//triangle collision
	bool collision(ray& ray, glm::vec3& intersectionpoint) override;

	//triangle normal
	glm::vec3 Normal() override;

protected:
	//triangle variable
	glm::vec3 points[3];
	glm::vec3 normal;
};

class Rectangle : public Object {
public:
	Rectangle() = default;

	//rectangle constructor
	Rectangle(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3,glm::vec3 point4, glm::vec3 rectanglecolor, int inmaterial) {
		//corners of the rectangle
		points[0] = point1;
		points[1] = point2;
		points[2] = point3;
		points[3] = point4;
		normal = Normal();
		color = rectanglecolor;
		material = inmaterial;
	}

	bool intersecNormal(ray& ray) override;

	//rectangle collision
	bool collision(ray& ray, glm::vec3& intersectionpoint) override;

	//rectangle normal
	glm::vec3 Normal() override;


protected:
	//rectangle variables
	glm::vec3 points[4];
	glm::vec3 normal;
};