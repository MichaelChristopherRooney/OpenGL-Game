#include <Resources\Game.h>

Game::Game(){

}

/* initialise everything needed to run the game */
bool Game::init(){

	// fatal if opengl and the shader cannot initialise
	if (!initOpenGL()){
		printf("Error in creating OpenGL instance\n");
		return false;
	}
	
	shader = new Shader();
	if (!shader->createShader()){
		printf("Error creating shader\n");
		return false;
	}

	player = new Player();
	input = new Input();
	camera = new Camera();
	light = new Light();
	physics = new Physics();
	textures = new TextureData();
	models = new ModelData();

	map = new Map();

	modelMatrix = glm::mat4(1.0f);

	glfwSetCursorPos(window, xRes / 2, yRes / 2); // stops camera starting at the wrong location

	return true;

}

bool Game::initOpenGL(){
	
	window = NULL;

	const GLubyte* renderer;
	const GLubyte* version;

	if (!glfwInit()){
		return 1;
	}

	window = glfwCreateWindow(xRes, yRes, "Game", NULL, NULL);

	if (!window){
		return 1;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

}

void Game::runTick(){

	currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glfwPollEvents();

	shader->setActive();

	input->update();
	player->update();
	camera->updateAngles();
	camera->updatePosition();
	light->update();

	physics->checkForHit();

	map->drawBlocks();
	player->draw();

	glUniformMatrix4fv(shader->shaderIDs.at("model"), 1, GL_FALSE, &modelMatrix[0][0]);

	glfwSwapBuffers(window);

}