#include "Object.h"
#include "ray.h"



//Sphere
//används inte men får fnatt om vi inte har en efterso mdet är en subclass
bool Sphere::intersecNormal(ray& ray) {
	return false;
}

//sphere collision
bool Sphere::collision(ray& ray, glm::vec3& intersectionpoint) {

	//formel för kollisonen av en sfär
	glm::vec3 SminusC = ray.originpoint() - position;
	double c1 = glm::dot(ray.direction(), ray.direction());
	double c2 = glm::dot(ray.direction() * glm::vec3(2.0,2.0,2.0),SminusC);
	double c3 = glm::dot(SminusC,SminusC) - pow(radius,2);
	double arg = pow(c2, 2) - (4.0 * c1 * c3);
	double t;

	//checka om den kolliderar
	if (pow((c2 / 2.0f), 2) - c3 > 0.0f) {
		float d1 = -(c2 / 2.0f) - sqrt(pow((c2 / 2.0f), 2) - c3);
		float d2 = -(c2 / 2.0f) + sqrt(pow((c2 / 2.0f), 2) - c3);

		//ta den närmsta av kollisionerna eftersom sfärer har två
		t = std::min(d1, d2);

		//definera de två kollisionerna
		glm::vec3 pos1 = (ray.originpoint() + d1 * ray.direction());
		glm::vec3 pos2 = (ray.originpoint() + d2 * ray.direction());

		//checka vilken som är den närmsta kollisionen
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
	//om den inte kolliderade returnera false
	return false;
}

//return the spheres normal
glm::vec3 Sphere::Normal() {
	return normal;
}

//triangle
bool Triangle::intersecNormal(ray& ray) {

	//checka normalen
	if (glm::dot(normal,ray.direction()) < 0)
	{
		return true;
	}
	else {
		return false;
	}
}

//triangle collision
bool Triangle::collision(ray& ray, glm::vec3& intersectionpoint) {
	
	//formel för triangel kollision
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

	if (t < 0.001)
	{
		return false;
	}

	//checka om dens intersektion är rätt
	if (intersecNormal(ray)) {


		//bestäm var intersection kolliderar
		intersectionpoint.x = ray.originpoint().x + (t * ray.direction().x);
		intersectionpoint.y = ray.originpoint().y + (t * ray.direction().y);
		intersectionpoint.z = ray.originpoint().z + (t * ray.direction().z);

		//checka om den kolliderar
		if ((0.0 <= u && 0.0 <= v && (u + v) <= 1.0) || (abs(u) <= 0.0001 && 0.0 <= v <= 1.0) || (abs(v) <= 0.0001 && 0.0 <= u <= 1.0))
		{	
			//sätt intersectionpunkten lite över objektet
			intersectionpoint += (normal * glm::vec3(0.001, 0.001, 0.001));

			return true;
		}
	}
	//om den inte kolliderade returnera false
	return false;
}

//beräkna triangelns normal
glm::vec3 Triangle::Normal() {
	glm::vec3 edge0to1 = points[1] - points[0];
	glm::vec3 edge0to2 = points[2] - points[0];

	return glm::normalize(glm::cross(edge0to1, edge0to2));
}

//samma som med triangel
bool Rectangle::intersecNormal(ray& ray) {
	if (glm::dot(normal, ray.direction()) < 0)
	{
		return true;
	}
	else {
		return false;
	}
}

//rektangel kollision
bool Rectangle::collision(ray& ray, glm::vec3& intersectionpoint) {
	
	//variabler för formeln
	glm::vec3 c1 = points[1] - points[0];
	glm::vec3 c2 = points[2] - points[0];
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

	//checka hållet av rektangeln så vi inte rendrerar baksidan
	if (intersecNormal(ray)) {


		//bestäm intersektionpunkten
		intersectionpoint.x = ray.originpoint().x + (t * ray.direction().x);
		intersectionpoint.y = ray.originpoint().y + (t * ray.direction().y);
		intersectionpoint.z = ray.originpoint().z + (t * ray.direction().z);
		double a = glm::dot((intersectionpoint - points[0]), c1) / glm::dot(c1, c1);
		double b = glm::dot((intersectionpoint - points[0]), c2) / glm::dot(c2, c2);
		
		//checka om vi kolliderar
		if ((0.0 <= a && a <= 1.0 && 0.0 <= b && b <= 1.0) || (abs(a) <= 0.0001 && 0.0 <= b && b <= 1.0) || (abs(b) <= 0.0001 && 0.0 <= a && a <= 1.0))
		{	
			//sätt intersectionpunkten lite över objektet
			intersectionpoint += (normal * glm::vec3(0.001, 0.001, 0.001));
			return true;
		}
	}
	//returnera false om vi inte kolliderade
	return false;
}

//returnera normalen av rektangeln
//samma som triangel
glm::vec3 Rectangle::Normal() {
	glm::vec3 edge0to1 = points[1] - points[0];
	glm::vec3 edge0to2 = points[2] - points[0];

	return glm::normalize(glm::cross(edge0to1, edge0to2));
}
