#include "scene.h"

Scene::Scene(){}

void Scene::addSphere(Sphere object) {
	sceneSpheres.push_back(object);
}

void Scene::addTriangle(Triangle object) {
	sceneTriangles.push_back(object);
}

void Scene::addLight(Light light) {
	sceneLights.push_back(light);
}
