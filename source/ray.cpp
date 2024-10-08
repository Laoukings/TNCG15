#include "ray.h"
	
	//default constructor
	ray::ray(glm::vec3 originpoint, glm::vec3 direction, glm::vec3 raycolor, ray* previousray, ray* nextray)
	: origin(originpoint), dir(direction), color(color), previous(previousray), next(nextray) {}

	//gauss random funktion
	glm::vec3 ray::Gauss(glm::vec3 normal) {
		//random device
		std::random_device rd;
		std::mt19937 mt(rd());
		std::normal_distribution<double> normdist(0.0, 1.0);

		double randval = normdist(mt);
		//if value is correct
		while (randval < -0.95 ||  randval > 0.95)
		{
			randval = normdist(mt);
		}

		//formula
		std::uniform_real_distribution<double> evendist(-1.0, 1.0);

		float theta = std::atan2(normal.y, normal.x) + (2.0 * 3.14159265 * evendist(mt));
		float phi = std::acos(normal.z / std::sqrt(glm::dot(normal, normal))) + (0.5 * 3.14159265 * randval);

		glm::vec3 randvec(std::sin(phi) * std::cos(phi), std::sin(phi) * std::sin(theta), std::cos(phi));

		randvec = glm::normalize(randvec);

		if (glm::dot(randvec,normal) <= 0) {
			randvec = -randvec;
		}
		//return random vector
		return randvec;
	}

	//mega function for calculating ray color
	glm::vec3 ray::Raycolorcalc(int reflectionamount, Scene& scene) {

		//variables
		glm::vec3 intersec;
		Object* nearestObject = nullptr;
		//high max values outside of scene
		float nearestColl = 10000000000000000.0;
		double t = 10000000000000000000000.0;

		//check which object is closest and intersects
		for (int i = 0; i < scene.getTriangles().size(); i++)
		{	

			if(scene.getTriangles()[i].collision(*this,intersec))
			{	
				t = glm::length(intersec - origin);
				if (t < nearestColl)
				{
					nearestObject = &(scene.getTriangles()[i]);
					nearestColl = t;
				}
			}
		}

		for (int i = 0; i < scene.getRectangle().size(); i++)
		{

			if (scene.getRectangle()[i].collision(*this, intersec))
			{
				t = glm::length(intersec - origin);

				if (t < nearestColl)
				{
					nearestObject = &(scene.getRectangle()[i]);
					nearestColl = t;
				}
			}
		}

		for (int i = 0; i < scene.getSpheres().size(); i++)
		{

			if (scene.getSpheres()[i].collision(*this, intersec))
			{
				t = glm::length(intersec - origin);
				if (t < nearestColl)
				{
					nearestObject = &(scene.getSpheres()[i]);
					nearestColl = t;
				}
			}
		}

		//maybe wrong
		glm::vec3 combinedcolor(0,0,0);

		//check for nullptrs
		if (nearestObject != nullptr) {

			end = intersec;

			//check all lights
			for (int i = 0; i < scene.getLights().size(); i++)
			{
				//check material room tba
				if (nearestObject->getMaterial() == 1)
				{
					glm::vec3 newdir = direction() - (glm::vec3(2.0,2.0,2.0) * glm::dot(direction(),nearestObject->Normal()) * nearestObject->Normal());
					ray newray(end,newdir);
					glm::vec3 reflectedcolor = newray.Raycolorcalc(reflectionamount - 1, scene);

					delete this->next;
					this->next = nullptr;

					combinedcolor += reflectedcolor;
				}
				else if (nearestObject->getMaterial() == 2) {
					combinedcolor = scene.getLights()[i].Color();
					return combinedcolor;
				}
				else {
					//shadowray
					//lite skumt
					combinedcolor = (nearestObject->getColor() * glm::vec3(0.5, 0.5, 0.5)) + this->Shadowray(nearestObject, &scene.getLights()[i], scene);
				}

			}
			end = intersec;
		}

		glm::vec3 randvec;
		//blir nullptr ibland
		if (nearestObject != nullptr) {
			//recursive function
			if (reflectionamount > 0) {
				randvec = Gauss(nearestObject->Normal());
				next = new ray(end, randvec);
				//lite skum
				glm::vec3 lightcolor = next->Raycolorcalc(reflectionamount - 1, scene);

				delete this->next;
				this->next = nullptr;

				combinedcolor += lightcolor;
				return combinedcolor;
			}
		}

		//if (nearestObject != nullptr) {
		//	return nearestObject->getColor();
		//}

		return combinedcolor;
	}

	glm::vec3 ray::Shadowray(Object* object, Light* light, Scene scene) {

		glm::vec3 shadow(0, 0, 0);
		glm::vec3 lightp = light->Randompoint();

		//skumt namn
		double darkper = 1.0;
		glm::vec3 intersec;
		glm::vec3 collisionpoint(0, 0, 0);

		//amount of rays
		int shadowamount = 5;

		for (int j = 0; j < shadowamount; j++)
		{	
			//variables
			glm::vec3 distance = lightp - end;
			double distancelength = glm::length(distance);
			double maxlength = std::numeric_limits<double>::max();

			ray shadowray(end, glm::normalize(distance));

			//v�ldigt os�ker p� pointers kan leda till fel
			for (int i = 0; i < scene.getTriangles().size(); i++)
			{
				if (&scene.getTriangles()[i] != object && scene.getTriangles()[i].collision(shadowray,collisionpoint)) {
					//if the length to the object is shorther than where it should hit
					if (glm::length(collisionpoint - end) + 0.001 < maxlength)
					{
						maxlength = glm::length(collisionpoint - end) + 0.001;
					}
				}
				
			}

			for (int i = 0; i < scene.getRectangle().size(); i++)
			{
				if (&scene.getRectangle()[i] != object && scene.getRectangle()[i].collision(shadowray, collisionpoint)) {
					if (glm::length(collisionpoint - end) + 0.001 < maxlength)
					{
						maxlength = glm::length(collisionpoint - end) + 0.001;
					}
				}
				
			}

			for (int i = 0; i < scene.getSpheres().size(); i++)
			{
				if (&scene.getSpheres()[i] != object && scene.getSpheres()[i].collision(shadowray, collisionpoint)) {
					if (glm::length(collisionpoint - end) + 0.001 < maxlength)
					{
						maxlength = glm::length(collisionpoint - end) + 0.001;
					}
				}
			
			}

			//check if it hit anything
			if (maxlength < distancelength) {
				darkper = 0.0;
			}

			//formuler
			double thetax = glm::dot(glm::normalize(object->Normal()), glm::normalize(distance));
			double thetay = glm::dot(light->position.Normal(), glm::normalize(distance));

			double div = pow(abs(distancelength), 2);

			double lambda = std::max((darkper * light->Area() * 3.14159265 * thetax * (-thetay)) / div, 0.0);
			shadow += glm::vec3(lambda, lambda, lambda);
		}

		//set the calue of shadow
		shadow = glm::vec3(shadow.x / (shadowamount / 6.0), shadow.y / (shadowamount / 6.0), shadow.z / (shadowamount / 6.0) );

		return shadow;
	}
