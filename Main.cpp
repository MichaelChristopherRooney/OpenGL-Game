#include <GL/glew.h> /* include this file first. this includes the newest gl.h header file on the system */
#include <GLFW/glfw3.h> /* handles creating a GL context, starting a window, and keyboard input etc. */
#include <stdio.h>
#include <Resources\Game.h>

Game *game;
int fps = 30;

int main() {

	game = new Game();

	if (!game->init()){
		printf("Error in initialising game. Press enter to continue.......\n");
		getchar();
		return 1;
	}

	while (!glfwWindowShouldClose(game->window)) {

		while ((glfwGetTime() - game->lastTime) < (1 / fps)){}

		game->runTick();

	}

	return 0;

}