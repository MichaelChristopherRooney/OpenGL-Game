#include <Resources\Game.h>

Game::Game(){
	model = new Model();
}

/* initialise everything needed to run the game */
bool Game::init(){

	
	if (!initOpenGL()){
		printf("Error in creating OpenGL instance\n");
		return false;
	}

	printf("OpenGL initialised\n");
	
	shader = new Shader();
	if (!shader->createShader()){
		printf("Error creating shader\n");
		return false;
	}

	player = new Player();

	printf("Shader initialised\n");

	input = new Input();
	camera = new Camera();

	modelMatrix = glm::mat4(1.0f);

	map = new Map();

	if (!map->createMap()){
		printf("Error creating map\n");
		return false;
	}

	printf("Map created\n");
	/*
	glUniformMatrix4fv(shader->shaderIDs.at("model"), 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(shader->shaderIDs.at("projection"), 1, GL_FALSE, &camera->projection[0][0]);
	glUniformMatrix4fv(shader->shaderIDs.at("view"), 1, GL_FALSE, &camera->view[0][0]);

	light = new Light();
	glUniform3fv(shader->shaderIDs.at("lightPosition"), 1, &light->lightPosition[0]);
	glUniform3fv(shader->shaderIDs.at("lightSpecular"), 1, &light->lightSpecular[0]);
	glUniform3fv(shader->shaderIDs.at("lightDiffuse"), 1, &light->lightDiffuse[0]);
	glUniform3fv(shader->shaderIDs.at("lightAmbient"), 1, &light->lightAmbient[0]);
	*/
	return true;

}

bool Game::initOpenGL(){
	
	window = NULL;

	const GLubyte* renderer;
	const GLubyte* version;

	if (!glfwInit()){
		return 1;
	}

	window = glfwCreateWindow(xRes, yRes, "Cube Game", NULL, NULL);

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

}

void Game::runTick(){

	currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glfwPollEvents();
	input->update();

	shader->setActive();

	map->drawBlocks();

	player->update();
	player->playerModel->draw();

	
	camera->update();

	glUniformMatrix4fv(shader->shaderIDs.at("model"), 1, GL_FALSE, &modelMatrix[0][0]);

	glfwSwapBuffers(window);

}