#include <Resources\Game.h>

Input::Input(){

	keys.insert({
		{ "W", false },
		{ "A", false },
		{ "S", false },
		{ "D", false },
		{ "SPACE", false },
		{ "CTRL", false }
	});

	mouseX = 0;
	mouseY = 0;


}

void Input::update(){

	if (glfwGetKey(game->window, GLFW_KEY_W)){
		keys.at("W") = true;
	}else{
		keys.at("W") = false;
	}

	if (glfwGetKey(game->window, GLFW_KEY_A)){
		keys.at("A") = true;
	}else{
		keys.at("A") = false;
	}

	if (glfwGetKey(game->window, GLFW_KEY_S)){
		keys.at("S") = true;
	}else{
		keys.at("S") = false;
	}

	if (glfwGetKey(game->window, GLFW_KEY_D)){
		keys.at("D") = true;
	}else{
		keys.at("D") = false;
	}

	if (glfwGetKey(game->window, GLFW_KEY_SPACE)){
		keys.at("SPACE") = true;
	}else{
		keys.at("SPACE") = false;
	}

	if (glfwGetKey(game->window, GLFW_KEY_LEFT_CONTROL)){
		keys.at("CTRL") = true;
	}else{
		keys.at("CTRL") = false;
	}

	if (glfwGetKey(game->window, GLFW_KEY_ESCAPE)){

	}

	glfwGetCursorPos(game->window, &mouseX, &mouseY);
	//glfwSetCursorPos(game->window, game->xRes / 2, game->yRes / 2);
	
}