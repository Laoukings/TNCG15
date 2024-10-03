
#include <glm.hpp>

class ray {
public:
	//default constructor with all needed elements
	ray(glm::vec3 originpoint, glm::vec3 direction, glm::vec3 raycolor, ray* previousray, ray* nextray);

	glm::vec3 originpoint() { return origin; }
	glm::vec3 direction() { return dir; }
	glm::vec3 raycolor() { return color; }



private:
	glm::vec3 origin = glm::vec3(0,0,0);
	glm::vec3 dir = glm::vec3(0, 0, 0);
	glm::vec3 color = glm::vec3(0, 0, 0);
	ray* previous = nullptr;
	ray* next = nullptr;

};