#pragma once

#include "Object.h"
#include "Light.h"
#include <vector>


class Scene
{
public:
	Scene();

	void addSphere(Sphere object);
	void addTriangle(Triangle object);
	void addLight(Light light);
	std::vector<Sphere>& getSpheres() { return sceneSpheres; }
	std::vector<Triangle>& getTriangles() { return sceneTriangles; }
	std::vector<Light>& getLights() { return sceneLights; }

private:
	std::vector<Sphere> sceneSpheres;
	std::vector<Triangle> sceneTriangles;
	std::vector<Light> sceneLights;

};

