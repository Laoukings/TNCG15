#include "scene.h"

//scen konstruktor
Scene::Scene(){}

//lägg till en sfär i scenen
void Scene::addSphere(Sphere object) {
	Objects.push_back(std::make_shared<Sphere>(object));
}

//lägg till en triangel i scenen
void Scene::addTriangle(Triangle object) {
	Objects.push_back(std::make_shared<Triangle>(object));
}

//lägg till en rektangel i scenen
void Scene::addRectangle(Rectangle object) {
	Objects.push_back(std::make_shared<Rectangle>(object));
}

//lägg till en lampa i scenen
void Scene::addLight(Light light) {
	sceneLights.push_back(light);
	Objects.push_back(std::make_shared<Rectangle>(light.position));
}
