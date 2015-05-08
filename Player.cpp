#include <Resources\Game.h>
#include <math.h>
#include <cmath>

Player::Player(){

	playerModel = new Model();
	playerModel->initFromFile("Assets/Models/cube.obj");
	playerModel->setTexture("Assets/Textures/metal.jpg");
	playerModel->translate(3, playerModel->yLen, 3);

}

void Player::draw(){
	playerModel->draw();
}

void Player::update(){

	float angle = game->camera->horizontalAngle;

	float sideSpeed = 0;
	float forwardSpeed = 0;

	if (game->input->keys.at("W")){
		forwardSpeed += playerSpeed * -sin(angle) * game->deltaTime;
		sideSpeed += playerSpeed * -cos(angle) * game->deltaTime;
	}

	if (game->input->keys.at("S")){
		forwardSpeed -= playerSpeed * -sin(angle) * game->deltaTime;
		sideSpeed -= playerSpeed * -cos(angle) * game->deltaTime;
	}

	if (game->input->keys.at("A")){
		forwardSpeed += playerSpeed * -cos(angle) * game->deltaTime;
		sideSpeed += playerSpeed * sin(angle) * game->deltaTime;
	}

	if (game->input->keys.at("D")){
		forwardSpeed += playerSpeed * cos(angle) * game->deltaTime;
		sideSpeed += playerSpeed * -sin(angle) * game->deltaTime;
	}

	// need to stop moving diagonally being faster

	playerModel->tx += forwardSpeed;
	playerModel->tz += sideSpeed;

	playerModel->translate();

}