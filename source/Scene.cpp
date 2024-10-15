#include "scene.h"

//scene constructor
Scene::Scene(){}

//add a sphere into the scene
void Scene::addSphere(Sphere object) {
	Objects.push_back(std::make_shared<Sphere>(object));
}

//add a triangle into the scene
void Scene::addTriangle(Triangle object) {
	Objects.push_back(std::make_shared<Triangle>(object));
}

//add rectangle
void Scene::addRectangle(Rectangle object) {
	Objects.push_back(std::make_shared<Rectangle>(object));
}

//add a light into the scene
void Scene::addLight(Light light) {
	sceneLights.push_back(light);
	Objects.push_back(std::make_shared<Rectangle>(light.position));
}
