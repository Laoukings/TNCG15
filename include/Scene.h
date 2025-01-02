#pragma once

#include "Object.h"
#include "Light.h"
#include <vector>
#include <Memory>


class Scene
{
public:
	//konstruktor
	Scene();

	//lägg till objekt i scenen
	void addSphere(Sphere object);
	void addTriangle(Triangle object);
	void addRectangle(Rectangle object);
	void addLight(Light light);

	//hämta objekt i scenen
	std::vector<Light>& getLights() { return sceneLights; }
	std::vector<std::shared_ptr<Object>>& getObjects() { return Objects; }

private:
	//vectorer med alla objekt
	std::vector<Light> sceneLights;
	std::vector<std::shared_ptr<Object>> Objects;

};

