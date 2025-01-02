#include "ray.h"
#include <iostream>

	
	//default constructor
	ray::ray(glm::vec3 originpoint, glm::vec3 direction, glm::vec3 color, ray* previousray, ray* nextray)
	: origin(originpoint), importance(color), previous(previousray), next(nextray) {
	
		dir = glm::normalize(direction);
	}

	//gauss random funktion
	glm::vec3 ray::Gauss(glm::vec3 normal) {
		//random device som ger oss en normalfördelning
		std::random_device rd;
		std::mt19937 mt(rd());
		//normalfördelning
		std::normal_distribution<double> normdist(0.0, 1.0);
		double randval = normdist(mt);

		//formel
		std::uniform_real_distribution<double> evendist(-1.0, 1.0);
		float theta = std::atan2(normal.y, normal.x) + (2.0 * 3.14159265 * evendist(mt));
		float phi = std::acos(normal.z / std::sqrt(glm::dot(normal, normal))) + (0.5 * 3.14159265 * randval);
		glm::vec3 randvec(std::sin(phi) * std::cos(phi), std::sin(phi) * std::sin(theta), std::cos(phi));
		randvec = glm::normalize(randvec);
		if (glm::dot(randvec,normal) <= 0) {
			randvec = -randvec;
		}
		return randvec;
	}

	glm::vec3 ray::Render(glm::vec3 _importance, Scene &scene) {
		//Definiera värden som ska ändras
		importance = _importance;
		glm::vec3 intersectionpoint = glm::vec3(0.0f);
		//sätt maxlängd långt utanför scenen
		double maxlengthtointersec = 100000000000000000000000.0;
		double lengthtointersec = 100000000000000000000000.0;
		std::shared_ptr<Object> hitObject = nullptr;
		glm::vec3 color(0.0f);

		//kolla vilket objekt strålen träffar
		for (int i = 0; i < scene.getObjects().size(); i++)
		{	
			//true om den kolliderar
			if (scene.getObjects()[i]->collision(*this,intersectionpoint))
			{
				lengthtointersec = glm::length(intersectionpoint - this->originpoint());
				this->end = intersectionpoint;

				//checka om det är närmsta kollisionen hitills
				if (maxlengthtointersec > lengthtointersec) {
					maxlengthtointersec = lengthtointersec;
					//bestäm att vi träffade det objektet
					hitObject = scene.getObjects()[i];
					surface = scene.getObjects()[i];
				}

			}
		}

		//antalet shadowrays
		int shadowrayamount = 5;
		//variabler för rendreringen
		double Le = 0.1/scene.getLights().size();
		float lightvalue = 0.0;

		//checka om strålen träffat något
		if (hitObject != nullptr) {
			//snabb funktion för om vi vill göra tester på kollision utan rendreringsformeln
			//return hitObject->getColor();

			//checka om objektet är ett ljus
			if (hitObject->getMaterial() == 2) {
				return hitObject->getColor() * importance;
			}


			//checka om objektet är en lambertian reflector
			if (hitObject->getMaterial() == 0) {

		
				//gå igenom alla ljus
				for (int i = 0; scene.getLights().size() > i; i++) {

					//kommer bli större baserad på hur mycket ljus
					double sum = 0.0;

					//går igenom alla shadowrays
					for (int j = 0; j < shadowrayamount; j++)
					{
						//ta en slumpmässig punkt på ljuset
						glm::vec3 pointonlight = scene.getLights()[i].Randompoint();

						//gör en shadowray
						ray shadowray(end, pointonlight - end);

						//definera en intersectio
						glm::vec3 intersec;

						//beräkna längden mellan punkten på lampan och där strålen träffade
						double l = glm::length(pointonlight - end);
						//mängden ljus
						int V = 1;

						//checka alla objekt
						for (int n = 0; n < scene.getObjects().size(); n++)
						{	
							//checka om strålen kolliderar med ett objekt innan den träffar ljuset
							//checka också så att den inte kolliderar med sig själv
							if (scene.getObjects()[n] != hitObject && scene.getObjects()[n]->collision(shadowray, intersec)) {
								
								//om kollisionen är närmre än punkten på ljuset gör det till skugga
								double shadowrayLength = glm::length(intersec - end);
								if (shadowrayLength < l) {
									V = 0;

								}
							}

						}
						//formel för hur mycket ljus i punkten
						glm::vec3 di = pointonlight - end;
						glm::vec3 Ny = scene.getLights()[i].Normal();
						glm::vec3 Nx = hitObject->Normal();

						double omegacosx = glm::dot(Nx,glm::normalize(di));
						double omegacosy = glm::dot(-Ny,glm::normalize(di));

						double G = (omegacosx * omegacosy) / glm::dot(glm::normalize(di),glm::normalize(di));

						//addera på summan
						sum += V * G;
						
					}

					sum *= (scene.getLights()[i].Area() * Le) / shadowrayamount;
					lightvalue += sum;
				}

				//använd gauss funktionen för att skicka en stråle i en slumpmässig riktning baserad på normalen på det träffade objektet
				glm::vec3 randdir = Gauss(hitObject->Normal());
				ray lambert(end, randdir);

				//formel för beräkning av färg
				color = hitObject->getColor();
				color *= lightvalue * importance;
				glm::vec3 nextImportance = color * importance;

				//slumpmässig nummer som kollar om vi terminatear strålen eller inte
				double terminate = ((double)rand() * 3) / RAND_MAX;
				
				if (terminate < importance.x + importance.y + importance.z) {
					//om vi inte terminatear kallar vi på render funktionen igen om går en stråle djupare
					color += lambert.Render(nextImportance, scene);
				}
				else {
					//om vi terminatear strålen 
					color *= importance;
				}

			}
			//checkar om objektet är en spegel
			if (hitObject->getMaterial() == 1) {
				//gör en ny stråle som studsar på spegeln och ändrar inte färgen
				glm::vec3 d_o = this->dir - 2.0f * glm::dot(this->dir, hitObject->Normal()) * hitObject->Normal();
				ray mirror(end, d_o);
				return mirror.Render(importance, scene);
			}
		}
		//retunerar färgen
		return color;
	}