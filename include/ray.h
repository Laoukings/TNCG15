
#include <glm.hpp>
#include "scene.h"
#include <random>

class ray {
public:
	//default constructor with all needed elements
	ray(glm::vec3 originpoint, glm::vec3 direction, glm::vec3 color = glm::vec3(0.0,0.0,0.0), ray* previousray = nullptr, ray* nextray = nullptr);

	//calc color in pixel
	glm::vec3 Raycolorcalc(ray& inray ,int reflectionamount, Scene& scene);
	glm::vec3 Shootray(ray& inray, int reflectionamount, Scene& scene);
	glm::vec3 Raylist(Scene& scene, glm::vec3 input, ray* prevray);
	glm::vec3 terminateRay(Scene& scene);
	glm::vec3 Gauss(glm::vec3 normal);
	glm::vec3 Shadowray(std::shared_ptr<Object>& object, Light& light, Scene scene);

	//reach variables
	glm::vec3 originpoint() { return origin; }
	glm::vec3 direction() { return dir; }
	glm::vec3 raycolor() { return color; }

	ray* previous;
	ray* next;
	std::shared_ptr<Object> surface;

private:
	//variables
	glm::vec3 origin;
	glm::vec3 dir;
	glm::vec3 end;
	glm::vec3 color;

};