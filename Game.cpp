#include <Resources\Game.h>

Game::Game(){

}

/* initialise everything needed to run the game */
bool Game::init(){

	
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
	textures = new TextureData();
	models = new ModelData();

	map = new Map();
	if (!map->createMap()){
		printf("Error creating map\n");
		return false;
	}

	modelMatrix = glm::mat4(1.0f);

	glfwSetCursorPos(window, xRes / 2, yRes / 2);

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

	renderer = glGetString(GL_RENDERER);
	version = glGetString(GL_VERSION);

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
	camera->updateAngles();
	player->update();
	camera->updatePosition();
	light->update();

	map->drawBlocks();
	player->draw();

	glUniformMatrix4fv(shader->shaderIDs.at("model"), 1, GL_FALSE, &modelMatrix[0][0]);

	glfwSwapBuffers(window);

}