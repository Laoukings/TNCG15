#include "ray.h"
#include <iostream>

	
	//default constructor
	ray::ray(glm::vec3 originpoint, glm::vec3 direction, glm::vec3 color, ray* previousray, ray* nextray)
	: origin(originpoint), importance(color), previous(previousray), next(nextray) {
	
		dir = glm::normalize(direction);
	}

	ray::ray(glm::vec3 originpoint, glm::vec3 direction, Scene& scene, glm::vec3 importans) {

		//initialized variabler
		rayscene = scene;
		origin = originpoint;
		dir = glm::normalize(direction);
		importance = importans;

		//variables for collision
		float nearestColl = 10000000000000000000000000000000000000000.0;
		double t = 10000000000000000000000.0;
		glm::vec3 intersec(0.0, 0.0, 0.0);

		for (int i = 0; i < rayscene.getObjects().size(); i++)
		{	

			if (rayscene.getObjects()[i]->collision(*this, intersec)) {

				t = glm::length(intersec - origin);

				if (t < nearestColl) {
					nearestColl = t;
					end = intersec;
					surface = rayscene.getObjects()[i];
				}
			}
		}

		if (surface != nullptr) {
			//debugging
			//std::cout << "yes";
			if (surface->getMaterial() == 0) {
				int num = rand();
				if (num%2 == 0) {
					glm::vec3 randvec = Gauss(surface->Normal());
					importance *= surface->getColor();
					ray lambert(end, randvec, rayscene, importance);
					next = &lambert;
					lambert.previous = this;
				}
				else {
					//tänka mer på
					importance *= surface->getColor();
				}
			}
			else if (surface->getMaterial() == 1) {
				glm::vec3 d_o = this->direction() - glm::vec3(2.0, 2.0, 2.0) * glm::dot(this->direction(), surface->Normal()) * surface->Normal();
				ray mirror(end, d_o, rayscene, importance);
				next = &mirror;
				mirror.previous = this;
			}
			else if (surface->getMaterial() == 2) {
				//just nu tar de alltid första lampans färg
				importance = rayscene.getLights()[0].Color();
			}
			else {
				importance = surface->getColor();
			}
			
		}
		else {
			//debugging
			//std::cout << "no";
		}


	}

	glm::vec3 ray::recursivecolor() {

		//while(next != nullptr) {
		//	importance = next->importance;
		//	next = next->next;
		//}

		glm::vec3 radiance(1.0, 1.0, 1.0);

		ray* radianceray;

		//if (next != nullptr) {
		//	radianceray = next;
		//}

		//if (next == nullptr) {
		//	return radiance;
		//}

		//while (next != nullptr) {
		//	//if (next->surface != nullptr) {
		//	//	if (next->surface->getMaterial() == 2) {
		//	//		radiance = next->surface->getColor();
		//	//	}
		//	//	else if (next->surface->getMaterial() == 0) {
		//	//		radiance = next->surface->getColor();
		//	//	}
		//	//}
		//	next = next->next;
		//}


		ray* dummy = this;

		while (next != nullptr) {
			dummy = next;
			next = next->next;
		}

		radianceray = dummy;
		

		int shadowrayamount = 5;
		//vet inte om den har något bestämt värde
		double Le = 3200.0;
		double lightvalue = 0.0;

		if(radianceray != nullptr){

			while (radianceray->previous != nullptr) {

				if (radianceray->surface != nullptr) {

					if (radianceray->surface->getMaterial() == 0) {

						for (int i = 0; rayscene.getLights().size() > i; i++) {
							double sum = 0.0;
							for (int j = 0; j < shadowrayamount; j++)
							{
								glm::vec3 pointonlight = rayscene.getLights()[i].Randompoint();
								ray shadowray(radianceray->end, pointonlight - radianceray->end);
								glm::vec3 intersec;
								//kanske borde vara abs
								double l = glm::length(pointonlight - radianceray->end);
								int V = 1;

								for (int n = 0; n < rayscene.getObjects().size(); n++)
								{	//vet inte hur den hanterar om objektet är ljudet eftersom den tekniskt sätt kommer collida med det alltid
									if (&rayscene.getObjects()[n] != &surface && rayscene.getObjects()[n]->collision(shadowray, intersec)) {
										//kanske borde vara abs
										if (glm::length(intersec - shadowray.originpoint()) < l) {
											V = 0;

										}
									}
								}

								glm::vec3 di = pointonlight - radianceray->end;
								glm::vec3 Ny = rayscene.getLights()[i].Normal();
								glm::vec3 Nx = radianceray->surface->Normal();
								double omegacosx = glm::dot(Nx, di / abs(di));
								double omegacosy = glm::dot(-Ny, di / abs(di));
								//l borde vara rätt
								double G = (omegacosx * omegacosy) / pow(l, 2);

								sum += V * G;
							}
							//om vi har flera light kommer sum ändras vilket är fel 
							sum *= (rayscene.getLights()[i].Area() * Le) / shadowrayamount;

							lightvalue = sum;
						}
						radiance = radianceray->importance * glm::vec3(lightvalue, lightvalue, lightvalue);

					}
					else if (radianceray->surface->getMaterial() == 2) {
						radiance = radianceray->surface->getColor();
					}
				}

				radianceray = radianceray->previous;

			}
		}

		return radiance;
	}

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
	glm::vec3 ray::Raycolorcalc(ray& inray, int reflectionamount, Scene& scene) {

		//variables
		glm::vec3 intersec;
		std::shared_ptr<Object> nearestObject = nullptr;
		//high max values outside of scene
		float nearestColl = 10000000000000000000000000000000000000000.0;
		double t = 10000000000000000000000.0;

		//check which object is closest and intersects
		// 
		// code before shared list
		// 
		//for (int i = 0; i < scene.getTriangles().size(); i++)
		//{	

		//	if(scene.getTriangles()[i].collision(*this,intersec))
		//	{	
		//		t = glm::length(intersec - origin);
		//		if (t < nearestColl)
		//		{
		//			nearestObject = &(scene.getTriangles()[i]);
		//			nearestColl = t;
		//		}
		//	}
		//}

		//for (int i = 0; i < scene.getRectangle().size(); i++)
		//{

		//	if (scene.getRectangle()[i].collision(*this, intersec))
		//	{
		//		t = glm::length(intersec - origin);

		//		if (t < nearestColl)
		//		{
		//			nearestObject = &(scene.getRectangle()[i]);
		//			nearestColl = t;
		//		}
		//	}
		//}

		//for (int i = 0; i < scene.getSpheres().size(); i++)
		//{

		//	if (scene.getSpheres()[i].collision(*this, intersec))
		//	{
		//		t = glm::length(intersec - origin);
		//		if (t < nearestColl)
		//		{
		//			nearestObject = &(scene.getSpheres()[i]);
		//			nearestColl = t;
		//		}
		//	}
		//}

		//maybe wrong
		glm::vec3 combinedcolor;
		glm::vec3 nearcolor(0.0,0.0,0.0);

		for (int j = 0; j < scene.getObjects().size(); j++)
		{
			if (scene.getObjects()[j]->collision(inray, intersec)) {

				t = glm::length(intersec - inray.origin);

				if (t < nearestColl)
				{
						nearestObject = scene.getObjects()[j];
						nearestColl = t;
						inray.end = intersec;

						//check lights
						for (int i = 0; i < scene.getLights().size(); i++)
						{	

							//check material room tba
							if (nearestObject->getMaterial() == 1)
							{
								glm::vec3 newdir = this->direction() - ((glm::vec3(2.0, 2.0, 2.0) * glm::dot(direction(), nearestObject->Normal()) * nearestObject->Normal()));
								ray newray(intersec, newdir);
								glm::vec3 reflectedcolor = newray.Raycolorcalc(newray, reflectionamount - 1, scene);

								delete this->next;
								this->next = nullptr;

								nearcolor += reflectedcolor;
							}
							else if (nearestObject->getMaterial() == 2) {
								nearcolor = scene.getLights()[i].Color();
								return nearcolor;
							}
							else {
								//shadowray
								//lite skumt
								//combinedcolor = (nearestObject->getColor() * glm::vec3(0.05, 0.05, 0.05)) + inray.Shadowray(nearestObject, scene.getLights()[i], scene);
								nearcolor = (nearestObject->getColor() * glm::vec3(0.05, 0.05, 0.05)) + inray.Shadowray(nearestObject, scene.getLights()[i], scene);
							}

						}
						end = intersec;
				}

			}
		}



		glm::vec3 randvec;
		//blir nullptr ibland

		
			//recursive function
			if (reflectionamount > 0) {
				randvec = Gauss(nearestObject->Normal());
				next = new ray(end, randvec);
				//lite skum
				glm::vec3 lightcolor = this->next->Raycolorcalc(*this->next, reflectionamount - 1, scene);

				delete this->next;
				this->next = nullptr;

				combinedcolor = nearcolor + lightcolor;
				return combinedcolor;
			}
			
		
		//ibland är nearcolor 0.0,0.0,0.0
		combinedcolor = nearcolor;

		return combinedcolor;
	}

	glm::vec3 ray::Shadowray(std::shared_ptr<Object>& object, Light& light, Scene scene) {

		glm::vec3 shadow(0.0, 0.0, 0.0);

		//skumt namn
		double darkper = 1.0;
		glm::vec3 intersec;
		glm::vec3 collisionpoint(0, 0, 0);

		//amount of rays
		int shadowamount = 5;

		for (int j = 0; j < shadowamount; j++)
		{	
			//variables
			glm::vec3 lightp = light.Randompoint();
			glm::vec3 distance = lightp - end;
			double distancelength = glm::length(distance);
			double maxlength = std::numeric_limits<double>::max();

			ray shadowray(end, glm::normalize(distance));


			for (int i = 0; i < scene.getObjects().size(); i++)
			{
				if (scene.getObjects()[i] != object && scene.getObjects()[i]->collision(shadowray,collisionpoint)) {

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
			double thetay = glm::dot(light.position.Normal(), glm::normalize(distance));

			double div = pow(abs(distancelength), 2);

			double lambda = std::max((darkper * light.Area() * 3.14159265 * thetax * (-thetay)) / div, 0.0);
			shadow += glm::vec3(lambda, lambda, lambda);
		}

		//set the value of shadow
		shadow = glm::vec3(shadow.x / (shadowamount / 6.0), shadow.y / (shadowamount / 6.0), shadow.z / (shadowamount / 6.0) );

		return shadow;
	}

	glm::vec3 ray::Shootray(ray& inray, int reflectionamount, Scene& scene) {
		
		glm::vec3 intersec;
		std::shared_ptr<Object> nearestObject = nullptr;
		//high max values outside of scene
		float nearestColl = 10000000000000000000000000000000000000000.0;
		double t = 10000000000000000000000.0;

		glm::vec3 color(0, 0, 0);

		for (int i = 0; i < scene.getObjects().size(); i++)
		{
			if (scene.getObjects()[i]->collision(inray, intersec)) {

				t = glm::length(intersec - inray.origin);


				//std::cout << "closest object is " << i << '\n';

				if (t < nearestColl)	
				{	
					//flytta utanför mer effektivt
					nearestColl = t;
					end = intersec;

					if(scene.getObjects()[i]->getMaterial() == 0){

						color = scene.getObjects()[i]->getColor();

					} else if (scene.getObjects()[i]->getMaterial() == 1) {

						glm::vec3 d_o = dir - 2.0f * glm::dot(dir, scene.getObjects()[i]->Normal()) * scene.getObjects()[i]->Normal();
						ray mirror(end, d_o);
						color = mirror.Shootray(mirror, reflectionamount, scene);

						delete this->next;
						this->next = nullptr;
					}
					else if(scene.getObjects()[i]->getMaterial() == 2)
					{	
						color = scene.getLights()[0].Color();
					}
					else if (scene.getObjects()[i]->getMaterial() == 3) {

						color = scene.getObjects()[i]->getColor();
					}
				}
			}
		}


		return color;
	}

	glm::vec3 ray::Raylist(Scene& scene, glm::vec3 input, ray *prevray) {
		//assign object to ray

		previous = prevray;
		glm::vec3 intersec;

		//high max values outside of scene
		float nearestColl = 10000000000000000000000000000000000000000.0;
		double t = 10000000000000000000000.0;
		glm::vec3 listcolor(0.0, 0.0, 0.0);
		glm::vec3 importance = input;

		for (int i = 0; i < scene.getObjects().size(); i++)
		{
			if (scene.getObjects()[i]->collision(*this, intersec)) {

				t = glm::length(intersec - origin);

				if (t < nearestColl) {
					nearestColl = t;
					end = intersec;
					surface = scene.getObjects()[i];
				}
			}
		}

		if(surface == nullptr){
			return glm::vec3(0.0, 0.0, 0.0);
		}

		//create new ray depending on material
		//Mirror never terminates
		if (surface->getMaterial() == 1) {

			glm::vec3 d_o = dir - 2.0f * glm::dot(dir, surface->Normal()) * surface->Normal();
			ray mirror(end, d_o);
			next = &mirror;
			mirror.Raylist(scene, importance, this);
		}

		//room and light always terminate
		if (surface->getMaterial() == 2) {
			return listcolor = terminateRay(scene);
		}
		else if(surface->getMaterial() == 3) {
			return listcolor = terminateRay(scene);
		}
		
		//wrong random function
		int num = rand();

		//check if ray terminates
		if (surface->getMaterial() == 0 && num%2 == 0) {
			glm::vec3 randvec = Gauss(surface->Normal());
			ray lambert(end, randvec);
			next = &lambert;
			lambert.Raylist(scene, importance * surface->getColor(), this);
		}
		else {
			return listcolor = terminateRay(scene);
		}

		return listcolor;
	}

	glm::vec3 ray::terminateRay(Scene& scene) {

		glm::vec3 terminatecolor(1.0,1.0,1.0);
		

		while (previous != nullptr) {
			if (surface->getMaterial() == 0 || surface->getMaterial() == 3) {
				//color = Shadowray(surface, scene.getLights()[0], scene);
				terminatecolor = surface->getColor();
			}
			else if (surface->getMaterial() == 2) {
				terminatecolor = scene.getLights()[0].Color();
			}
			surface = previous->surface;
			previous = previous->previous;
			//delete this->next;
			//this->next = nullptr;
		}

		if (previous == nullptr) {
			if (surface->getMaterial() == 0 || surface->getMaterial() == 3) {
				//color = Shadowray(surface, scene.getLights()[0], scene);
				terminatecolor = surface->getColor();
			}
			else if (surface->getMaterial() == 2) {
				terminatecolor = scene.getLights()[0].Color();
			}
		}
	

		return terminatecolor;
	}

	glm::vec3 ray::Render(glm::vec3 _importance, Scene &scene) {
		importance = _importance;
		glm::vec3 intersectionpoint = glm::vec3(0.0f);
		double maxlengthtointersec = 100000000000000000000000.0;
		double lengthtointersec = 100000000000000000000000.0;
		std::shared_ptr<Object> hitObject = nullptr;
		glm::vec3 color(0.0f);

		for (int i = 0; i < scene.getObjects().size(); i++)
		{
			if (scene.getObjects()[i]->collision(*this,intersectionpoint))
			{
				lengthtointersec = glm::length(intersectionpoint - this->originpoint());
				this->end = intersectionpoint;

				if (maxlengthtointersec > lengthtointersec) {
					maxlengthtointersec = lengthtointersec;
					hitObject = scene.getObjects()[i];
					surface = scene.getObjects()[i];
				}

			}
		}

		int shadowrayamount = 5;
		double Le = 3200.0;
		float lightvalue = 0.0;

		if (hitObject != nullptr) {
			if (hitObject->getMaterial() == 2) {
				return scene.getLights()[0].Color();
			}
			if (hitObject->getMaterial() == 0) {




				for (int i = 0; scene.getLights().size() > i; i++) {

					double sum = 0.0;

					for (int j = 0; j < shadowrayamount; j++)
					{
						glm::vec3 pointonlight = scene.getLights()[i].Randompoint();

						//test ray shadowray(end, pointonlight - end);
						ray shadowray(end, end - pointonlight);
						glm::vec3 intersec;
						//kanske borde vara abs
						double l = glm::length(pointonlight - end);
						int V = 1;

						for (int n = 0; n < scene.getObjects().size(); n++)
						{	//vet inte hur den hanterar om objektet är ljuset eftersom den tekniskt sätt kommer collida med det alltid
							//if (scene.getObjects()[n]->isSame(hitObject) == false && scene.getObjects()[n]->collision(shadowray, intersec)) {
							if (scene.getObjects()[n]->isSame(hitObject) == false && scene.getObjects()[n]->collision(shadowray, intersec)) {
								//kanske borde vara abs
								double shadowrayLength = glm::length(intersec - end);
								if (shadowrayLength < l) {
									V = 0;

								}
							}
						}

						//glm::vec3 di = pointonlight - end;
						glm::vec3 di = pointonlight - end;
						glm::vec3 Ny = scene.getLights()[i].Normal();
						glm::vec3 Nx = hitObject->Normal();

						//double omegacosx = glm::dot(Nx, di / abs(di));
						//double omegacosy = glm::dot(-Ny, di / abs(di));

						double omegacosx = glm::dot(Nx,glm::normalize(di));
						double omegacosy = glm::dot(-Ny,glm::normalize(di));

						//double omegacosx = glm::dot(Nx,di / glm::normalize(di));
						//double omegacosy = glm::dot(-Ny,di / glm::normalize(di));
			
						//double G = (omegacosx * omegacosy) / pow(l, 2);
						double G = (omegacosx * omegacosy) / glm::dot(glm::normalize(di),glm::normalize(di));

						
						sum += V * G;
						//sum += G * 1;
					}
					//om vi har flera light kommer sum ändras vilket är fel 


					sum *= (scene.getLights()[i].Area() * Le) / shadowrayamount;
					//sum *= (scene.getLights()[i].Area()) / shadowrayamount;

					lightvalue = sum;


				}


				//glm::vec3 randdir = Gauss(hitObject->Normal());
				//ray lambert(end, randdir);

				//color = hitObject->getColor();
				//color *= lightvalue * importance;
				////antagligen fel
				//glm::vec3 nextImportance = hitObject->getColor();

				//double terminate = (double)rand() / RAND_MAX;
				//
				//if (terminate > 0.3) {


				//	color += lambert.Render(nextImportance, scene);
				//}
				//else {

				//	color *= importance;
				//}

				return hitObject->getColor() * lightvalue;
			}
			if (hitObject->getMaterial() == 1) {
				glm::vec3 d_o = this->dir - 2.0f * glm::dot(this->dir, hitObject->Normal()) * hitObject->Normal();
				ray mirror(end, d_o);
				return mirror.Render(importance, scene);
			}
		}

		return color;
	}