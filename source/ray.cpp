#include "ray.h"
#include <iostream>

	
	//default constructor
	ray::ray(glm::vec3 originpoint, glm::vec3 direction, glm::vec3 color, ray* previousray, ray* nextray)
	: origin(originpoint), importance(color), previous(previousray), next(nextray) {
	
		dir = glm::normalize(direction);
	}

	//gauss random funktion
	glm::vec3 ray::Gauss(glm::vec3 normal) {
		//random device som ger oss en normalf�rdelning
		std::random_device rd;
		std::mt19937 mt(rd());
		//normalf�rdelning
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
		//Definiera v�rden som ska �ndras
		importance = _importance;
		glm::vec3 intersectionpoint = glm::vec3(0.0f);
		//s�tt maxl�ngd l�ngt utanf�r scenen
		double maxlengthtointersec = 100000000000000000000000.0;
		double lengthtointersec = 100000000000000000000000.0;
		std::shared_ptr<Object> hitObject = nullptr;
		glm::vec3 color(0.0f);

		//kolla vilket objekt str�len tr�ffar
		for (int i = 0; i < scene.getObjects().size(); i++)
		{	
			//true om den kolliderar
			if (scene.getObjects()[i]->collision(*this,intersectionpoint))
			{
				lengthtointersec = glm::length(intersectionpoint - this->originpoint());
				this->end = intersectionpoint;

				//checka om det �r n�rmsta kollisionen hitills
				if (maxlengthtointersec > lengthtointersec) {
					maxlengthtointersec = lengthtointersec;
					//best�m att vi tr�ffade det objektet
					hitObject = scene.getObjects()[i];
					surface = scene.getObjects()[i];
				}

			}
		}

		//antalet shadowrays
		int shadowrayamount = 5;
		//variabler f�r rendreringen
		double Le = 0.1/scene.getLights().size();
		float lightvalue = 0.0;

		//checka om str�len tr�ffat n�got
		if (hitObject != nullptr) {
			//snabb funktion f�r om vi vill g�ra tester p� kollision utan rendreringsformeln
			//return hitObject->getColor();

			//checka om objektet �r ett ljus
			if (hitObject->getMaterial() == 2) {
				return hitObject->getColor() * importance;
			}


			//checka om objektet �r en lambertian reflector
			if (hitObject->getMaterial() == 0) {

		
				//g� igenom alla ljus
				for (int i = 0; scene.getLights().size() > i; i++) {

					//kommer bli st�rre baserad p� hur mycket ljus
					double sum = 0.0;

					//g�r igenom alla shadowrays
					for (int j = 0; j < shadowrayamount; j++)
					{
						//ta en slumpm�ssig punkt p� ljuset
						glm::vec3 pointonlight = scene.getLights()[i].Randompoint();

						//g�r en shadowray
						ray shadowray(end, pointonlight - end);

						//definera en intersectio
						glm::vec3 intersec;

						//ber�kna l�ngden mellan punkten p� lampan och d�r str�len tr�ffade
						double l = glm::length(pointonlight - end);
						//m�ngden ljus
						int V = 1;

						//checka alla objekt
						for (int n = 0; n < scene.getObjects().size(); n++)
						{	
							//checka om str�len kolliderar med ett objekt innan den tr�ffar ljuset
							//checka ocks� s� att den inte kolliderar med sig sj�lv
							if (scene.getObjects()[n] != hitObject && scene.getObjects()[n]->collision(shadowray, intersec)) {
								
								//om kollisionen �r n�rmre �n punkten p� ljuset g�r det till skugga
								double shadowrayLength = glm::length(intersec - end);
								if (shadowrayLength < l) {
									V = 0;

								}
							}

						}
						//formel f�r hur mycket ljus i punkten
						glm::vec3 di = pointonlight - end;
						glm::vec3 Ny = scene.getLights()[i].Normal();
						glm::vec3 Nx = hitObject->Normal();

						double omegacosx = glm::dot(Nx,glm::normalize(di));
						double omegacosy = glm::dot(-Ny,glm::normalize(di));

						double G = (omegacosx * omegacosy) / glm::dot(glm::normalize(di),glm::normalize(di));

						//addera p� summan
						sum += V * G;
						
					}

					sum *= (scene.getLights()[i].Area() * Le) / shadowrayamount;
					lightvalue += sum;
				}

				//anv�nd gauss funktionen f�r att skicka en str�le i en slumpm�ssig riktning baserad p� normalen p� det tr�ffade objektet
				glm::vec3 randdir = Gauss(hitObject->Normal());
				ray lambert(end, randdir);

				//formel f�r ber�kning av f�rg
				color = hitObject->getColor();
				color *= lightvalue * importance;
				glm::vec3 nextImportance = color * importance;

				//slumpm�ssig nummer som kollar om vi terminatear str�len eller inte
				double terminate = ((double)rand() * 3) / RAND_MAX;
				
				if (terminate < importance.x + importance.y + importance.z) {
					//om vi inte terminatear kallar vi p� render funktionen igen om g�r en str�le djupare
					color += lambert.Render(nextImportance, scene);
				}
				else {
					//om vi terminatear str�len 
					color *= importance;
				}

			}
			//checkar om objektet �r en spegel
			if (hitObject->getMaterial() == 1) {
				//g�r en ny str�le som studsar p� spegeln och �ndrar inte f�rgen
				glm::vec3 d_o = this->dir - 2.0f * glm::dot(this->dir, hitObject->Normal()) * hitObject->Normal();
				ray mirror(end, d_o);
				return mirror.Render(importance, scene);
			}
		}
		//retunerar f�rgen
		return color;
	}