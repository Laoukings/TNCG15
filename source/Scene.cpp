#include "scene.h"

//scene constructor
Scene::Scene(){}

//add a sphere into the scene
void Scene::addSphere(Sphere object) {
	sceneSpheres.push_back(object);
}

//add a triangle into the scene
void Scene::addTriangle(Triangle object) {
	sceneTriangles.push_back(object);
}

//add rectangle
void Scene::addRectangle(Rectangle object) {
	sceneRectangles.push_back(object);
}

//add a light into the scene
void Scene::addLight(Light light) {
	sceneLights.push_back(light);
}
