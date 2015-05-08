#include <Resources\Game.h>

Player::Player(){

	playerModel = new Model();
	playerModel->initFromFile("Assets/Models/cube.obj");
	playerModel->setTexture("Assets/Textures/metal.jpg");

}

void Player::updateAndDraw(){

	processInput();
	playerModel->draw();

}

void Player::processInput(){

	if (game->input->keys.at("W")){
		playerModel->tx += playerSpeed * game->deltaTime;
	}

	if (game->input->keys.at("S")){
		playerModel->tx -= playerSpeed * game->deltaTime;
	}

	if (game->input->keys.at("A")){
		playerModel->tz -= playerSpeed * game->deltaTime;
	}

	if (game->input->keys.at("D")){
		playerModel->tz += playerSpeed * game->deltaTime;
	}

	if (game->input->keys.at("SPACE")){
		playerModel->ty += playerSpeed * game->deltaTime;
	}

	if (game->input->keys.at("CTRL")){
		playerModel->ty -= playerSpeed * game->deltaTime;
	}

	playerModel->translate();

}