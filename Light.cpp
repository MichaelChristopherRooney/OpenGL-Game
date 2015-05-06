#include <Resources\Light.h>

Light::Light(){

	lightPosition = glm::vec3(1, 0, 1);
	lightSpecular = glm::vec3(1.0, 1.0, 1.0);
	lightDiffuse = glm::vec3(0.7, 0.7, 0.7);
	lightAmbient = glm::vec3(0.2, 0.2, 0.2);

}