#include <glm\glm.hpp>
#include <glm\ext.hpp>

class Light{

public:

	Light();
	void set_colour(float r, float g, float b);
	void set_position(float x, float y, float z);

	glm::vec3 lightPosition;
	glm::vec3 lightSpecular;
	glm::vec3 lightDiffuse;
	glm::vec3 lightAmbient;

};