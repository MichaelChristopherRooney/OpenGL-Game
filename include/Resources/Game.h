#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <glm\gtx\transform.hpp>

#include <Resources\Shader.h>
#include <Resources\Model.h>
#include <Resources\Input.h>
#include <Resources\Camera.h>
#include <Resources\Player.h>
#include <Resources\Map.h>

class Game{

public:

	Game();
	bool init();
	bool initOpenGL();
	void runTick();

	int xRes = 1600;
	int yRes = 900;

	float deltaTime = 0;
	float lastTime = 0;
	float currentTime = 0;

	GLFWwindow *window;
	Shader *shader;
	Model *model;
	Input *input;
	Camera *camera;
	Player *player;
	Map *map;

	glm::mat4 modelMatrix;

};