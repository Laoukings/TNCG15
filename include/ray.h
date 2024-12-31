
#include <glm.hpp>
#include "scene.h"
#include <random>

class ray {
public:
	//default constructor och funktion definitioner
	ray(glm::vec3 originpoint, glm::vec3 direction, glm::vec3 color = glm::vec3(0.0,0.0,0.0), ray* previousray = nullptr, ray* nextray = nullptr);
	glm::vec3 Gauss(glm::vec3 normal);
	glm::vec3 Render(glm::vec3 _importance, Scene& scene);

	//variabler vi vill nå
	glm::vec3 originpoint() { return origin; }
	glm::vec3 direction() { return dir; }
	glm::vec3 raycolor() { return importance; }

	//pointers
	ray *previous = nullptr;
	ray *next = nullptr;
	std::shared_ptr<Object> surface = nullptr;

private:
	//privata variabler
	glm::vec3 origin;
	Scene rayscene;
	glm::vec3 dir;
	glm::vec3 end = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 importance;

};