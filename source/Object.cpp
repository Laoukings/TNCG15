﻿#include "Object.h"
#include "ray.h"



//Sphere
//används inte
bool Sphere::intersecNormal(ray& ray) {
	return false;
}

//sphere collision
bool Sphere::collision(ray& ray, glm::vec3& intersectionpoint) {

	//formula
	glm::vec3 SminusC = ray.originpoint() - position;

	double c1 = glm::dot(ray.direction(), ray.direction());
	//b
	double c2 = glm::dot(ray.direction() * glm::vec3(2.0,2.0,2.0),SminusC);
	//c
	double c3 = glm::dot(SminusC,SminusC) - pow(radius,2);

	double arg = pow(c2, 2) - (4.0 * c1 * c3);

	double t;


	
	//check both the case of 1 intersection and 2
	//if (abs(arg) < 0.01) {
	//	intersectionpoint = ray.originpoint() + (ray.direction() * glm::vec3(-c2/2.0, -c2 / 2.0, -c2 / 2.0));
	//	normal = glm::normalize(intersectionpoint - position);
	//	return true;
	//} 

	//if (arg > 0.0) {
	//	//exception om inte i denna
	//	double tplus = (-c2 + sqrt(arg)) / (2.0 * c1);
	//	double tminus = (-c2 - sqrt(arg)) / (2.0 * c1);
	

	//	//check which t is smaller
	//	if (tplus < tminus) {
	//		t = tplus;
	//	}
	//	else {
	//		t = tminus;
	//	}

	//	//check if t is super small for intersection
	//	if (abs(t) < 0.001) {
	//		if (tminus <= 0.001 && tplus <= 0.001) {
	//			return false;
	//		}
	//		//change t to larger t
	//		if (tplus > tminus) {
	//			t = tplus;
	//		}
	//		else {
	//			t = tminus;
	//		}
	//	}

	//	intersectionpoint = ray.originpoint() + (glm::vec3(t, t, t) * ray.direction());
	//	normal = glm::normalize(intersectionpoint - position);
	//	//collision
	//	//intersectionpoint += normal * 0.01f;
	//	return true;
	//}

	//b = c2, c = c3
	if (pow((c2 / 2.0f), 2) - c3 > 0.0f) {
		float d1 = -(c2 / 2.0f) - sqrt(pow((c2 / 2.0f), 2) - c3);
		float d2 = -(c2 / 2.0f) + sqrt(pow((c2 / 2.0f), 2) - c3);

		t = std::min(d1, d2);

		glm::vec3 pos1 = (ray.originpoint() + d1 * ray.direction());
		glm::vec3 pos2 = (ray.originpoint() + d2 * ray.direction());


		if (glm::distance(pos1, ray.originpoint()) < 0.001 && d2 > 0.0f) {
			intersectionpoint = pos2;
			normal = glm::normalize(intersectionpoint - position);
			return true;
		}
		else if (d1 > 0.0f) {
			intersectionpoint = pos1;
			normal = glm::normalize(intersectionpoint - position);
			return true;
		}
	}

	return false;
}

//return the spheres normal
glm::vec3 Sphere::Normal() {
	return normal;
}

//triangle
bool Triangle::intersecNormal(ray& ray) {

	//check if normal is positive
	if (glm::dot(normal,ray.direction()) < 0)
	{
		return true;
	}
	else {
		return false;
	}
}

//triangle collision skum just nu skapar fyrkanter
//triangle collision
bool Triangle::collision(ray& ray, glm::vec3& intersectionpoint) {
	
	//edges
	glm::vec3 c1 = points[1] - points[0];
	glm::vec3 c2 = points[2] - points[0];
	glm::vec3 origintopoint = ray.originpoint() - points[0];
	glm::vec3 raycrossc1 = glm::cross(origintopoint, c1);
	glm::vec3 raycrossc2 = glm::cross(ray.direction(), c2);
	float det = glm::dot(raycrossc2, c1);
	float inverdet = (1 / det);

	float u = inverdet * glm::dot(raycrossc2, origintopoint);
	float v = inverdet * glm::dot(raycrossc1, ray.direction());
	float t = inverdet * glm::dot(raycrossc1, c2);
	//double t = glm::dot((points[0] - ray.originpoint()), normal) / glm::dot(ray.direction(), normal);


	if (t < 0.001)
	{
		return false;
	}

	//formula möller
	if (intersecNormal(ray)) {
		intersectionpoint.x = ray.originpoint().x + (t * ray.direction().x);
		intersectionpoint.y = ray.originpoint().y + (t * ray.direction().y);
		intersectionpoint.z = ray.originpoint().z + (t * ray.direction().z);
		//double a = glm::dot((intersectionpoint - points[0]), c1) / glm::dot(c1, c1);
		//double b = glm::dot((intersectionpoint - points[0]), c2) / glm::dot(c2, c2);

		//check collision
		if ((0.0 <= u && 0.0 <= v && (u + v) <= 1.0) || (abs(u) <= 0.001 && 0.0 <= v <= 1.0) || (abs(v) <= 0.001 && 0.0 <= u <= 1.0))
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


	glm::vec3 c1 = points[1] - points[0];
	glm::vec3 c2 = points[2] - points[0];

	//nytt försök för t kopierar triangeln
	glm::vec3 origintopoint = ray.originpoint() - points[0];
	glm::vec3 raycrossc1 = glm::cross(origintopoint, c1);
	glm::vec3 raycrossc2 = glm::cross(ray.direction(), c2);
	float det = glm::dot(raycrossc2, c1);
	float inverdet = (1 / det);
	float t = inverdet * glm::dot(raycrossc1, c2);

	if (t < 0.001)
	{
		return false;
	}

	if (intersecNormal(ray)) {

		//double t = glm::dot((points[0] - ray.originpoint()), normal) / glm::dot(ray.direction(), normal);

		intersectionpoint.x = ray.originpoint().x + (t * ray.direction().x);
		intersectionpoint.y = ray.originpoint().y + (t * ray.direction().y);
		intersectionpoint.z = ray.originpoint().z + (t * ray.direction().z);
		double a = glm::dot((intersectionpoint - points[0]), c1) / glm::dot(c1, c1);
		double b = glm::dot((intersectionpoint - points[0]), c2) / glm::dot(c2, c2);
		
		if ((0.0 <= a && a <= 1.0 && 0.0 <= b && b <= 1.0) || (abs(a) <= 0.001 && 0.0 <= b && b <= 1.0) || (abs(b) <= 0.001 && 0.0 <= a && a <= 1.0))
		{
			//intersectionpoint += (normal * glm::vec3(0.01, 0.01, 0.01));
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

glm::vec3 Sphere::getPos() {
	return position;
}

glm::vec3 Triangle::getPos() {
	return points[0];
}

glm::vec3 Rectangle::getPos() {
	return points[0];
}


bool Sphere::isSame(std::shared_ptr<Object> same) {
	if (abs(glm::length(position - same->getPos())) < 0.1) {
		return true;
	}
	return false;
}

bool Rectangle::isSame(std::shared_ptr<Object> same) {
	if (abs(glm::length(points[0] - same->getPos())) < 0.1) {
		return true;
	}
	return false;
}

bool Triangle::isSame(std::shared_ptr<Object> same) {
	if (abs(glm::length(points[0] - same->getPos())) < 0.1) {
		return true;
	}
	return false;
}
