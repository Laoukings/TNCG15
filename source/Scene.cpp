#include "scene.h"

//scen konstruktor
Scene::Scene(){}

//l�gg till en sf�r i scenen
void Scene::addSphere(Sphere object) {
	Objects.push_back(std::make_shared<Sphere>(object));
}

//l�gg till en triangel i scenen
void Scene::addTriangle(Triangle object) {
	Objects.push_back(std::make_shared<Triangle>(object));
}

//l�gg till en rektangel i scenen
void Scene::addRectangle(Rectangle object) {
	Objects.push_back(std::make_shared<Rectangle>(object));
}

//l�gg till en lampa i scenen
void Scene::addLight(Light light) {
	sceneLights.push_back(light);
	Objects.push_back(std::make_shared<Rectangle>(light.position));
}
