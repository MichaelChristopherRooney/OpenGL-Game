#include <Resources\Game.h>

Player::Player(){

	playerModel = new Model();
	playerModel->initFromFile("Assets/Models/cube.obj");

}

void Player::updateAndDraw(){

	if (game->input->keys.at("A")){
		playerModel->tz += playerSpeed * game->deltaTime;
	}

	if (game->input->keys.at("D")){
		playerModel->tz -= playerSpeed * game->deltaTime;
	}

	playerModel->translate(0, playerModel->yLen, playerModel->tz);

	playerModel->draw();

}