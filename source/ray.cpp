#include "ray.h"
	
	//default constructor
	ray::ray(glm::vec3 originpoint, glm::vec3 direction, glm::vec3 raycolor, ray* previousray, ray* nextray)
	: origin(originpoint), dir(direction), color(raycolor), previous(previousray), next(nextray) {}

	glm::vec3 ray::Raycolorcalc(int reflectionamount, Scene& scene) {


		glm::vec3 intersec(0, 0, 0);
		//if (scene.getSpheres()[0].collision(*this,intersec))
		//{
		//	return scene.getSpheres()[0].getColor();
		//}

		//if (scene.getSpheres()[1].collision(*this, intersec))
		//{
		//	return scene.getSpheres()[1].getColor();
		//}

		//if (scene.getRectangle()[0].collision(*this, intersec))
		//{
		//	return scene.getRectangle()[0].getColor();
		//}

		if (scene.getTriangles()[0].collision(*this, intersec))
		{
			return scene.getTriangles()[0].getColor();
		}
		if (scene.getTriangles()[1].collision(*this, intersec))
		{
			return scene.getTriangles()[1].getColor();
		}

		return glm::vec3(0, 0, 0);
	}