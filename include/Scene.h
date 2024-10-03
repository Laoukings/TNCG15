#pragma once

#include "Object.h"
#include "Light.h"
#include <vector>


class Scene
{
public:
	//constructor
	Scene();

	//add objects into scene
	void addSphere(Sphere object);
	void addTriangle(Triangle object);
	void addLight(Light light);

	//get the objects in the scene
	std::vector<Sphere>& getSpheres() { return sceneSpheres; }
	std::vector<Triangle>& getTriangles() { return sceneTriangles; }
	std::vector<Light>& getLights() { return sceneLights; }

private:
	//vectors with all objects
	std::vector<Sphere> sceneSpheres;
	std::vector<Triangle> sceneTriangles;
	std::vector<Light> sceneLights;

};

