#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <glm\gtx\transform.hpp>

#include <Resources\Shader.h>
#include <Resources\Model.h>
#include <Resources\Input.h>
#include <Resources\Camera.h>
#include <Resources\Map.h>
#include <Resources\Light.h>
#include <Resources\Texture.h>
#include <Resources\TextureData.h>
#include <Resources\ModelData.h>
#include <Resources\Physics.h>
#include <Resources\Player.h>

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
	Input *input;
	Camera *camera;
	Player *player;
	Map *map;
	Light *light;
	TextureData *textures;
	ModelData *models;
	Physics *physics;

	glm::mat4 modelMatrix;

};