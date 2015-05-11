#include <glm\glm.hpp>
#include <glm\ext.hpp>

class Game;
extern Game *game;

class Light{

public:

	Light();
	void setActive();
	void update();

	glm::vec3 lightPosition;
	glm::vec3 lightSpecular;
	glm::vec3 lightDiffuse;
	glm::vec3 lightAmbient;

};