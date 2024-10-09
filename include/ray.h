
#include <glm.hpp>
#include "scene.h"

class ray {
public:
	//default constructor with all needed elements
	ray(glm::vec3 originpoint, glm::vec3 direction, glm::vec3 raycolor, ray* previousray, ray* nextray);

	glm::vec3 Raycolorcalc(int reflectionamount, Scene& scene);

	//reach variables
	glm::vec3 originpoint() { return origin; }
	glm::vec3 direction() { return dir; }
	glm::vec3 raycolor() { return color; }

private:
	//variables
	glm::vec3 origin;
	glm::vec3 dir;
	glm::vec3 color;
	ray* previous = nullptr;
	ray* next = nullptr;

};