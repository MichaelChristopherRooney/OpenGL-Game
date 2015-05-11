#include <Resources\Game.h>
#include <math.h>
#include <cmath>

Player::Player(){

	playerModel = new Model();

	playerModel->initFromFile("Assets/Models/sphere.obj");
	playerModel->setTexture("Assets/Textures/blue.jpg");

	// position the model inside the game area
	playerModel->translate(3, playerModel->yLen / 2, 3);

}

void Player::draw(){
	playerModel->draw();
}

void Player::update(){

	handleInput();
	handlePhysics();

	playerModel->tx += xSpeed;
	playerModel->tz += zSpeed;

	playerModel->translate();

}

/*
get input and decide which direction the player is moving in
the player's direction is dependant upon the horizontal position of the camera
*/
void Player::handleInput(){

	if (game->input->keys.at("W")){
		xSpeed += acceleration * -sin(game->camera->horizontalAngle) * game->deltaTime;
		zSpeed += acceleration * -cos(game->camera->horizontalAngle) * game->deltaTime;
	}

	if (game->input->keys.at("S")){
		xSpeed -= acceleration * -sin(game->camera->horizontalAngle) * game->deltaTime;
		zSpeed -= acceleration * -cos(game->camera->horizontalAngle) * game->deltaTime;
	}

	if (game->input->keys.at("A")){
		xSpeed += acceleration * -cos(game->camera->horizontalAngle) * game->deltaTime;
		zSpeed += acceleration * sin(game->camera->horizontalAngle) * game->deltaTime;
	}

	if (game->input->keys.at("D")){
		xSpeed += acceleration * cos(game->camera->horizontalAngle) * game->deltaTime;
		zSpeed += acceleration * -sin(game->camera->horizontalAngle) * game->deltaTime;
	}

}

/*
ensure the player does not go above a certain speed
bounce the player away from any block they hit
*/
void Player::handlePhysics(){

	if (xSpeed > maxSpeed){
		xSpeed = maxSpeed;
	}

	if (zSpeed > maxSpeed){
		zSpeed = maxSpeed;
	}

	if (game->physics->negZHit){
		zSpeed = zSpeed * -1;
	}

	if (game->physics->posZHit){
		zSpeed = zSpeed * -1;
	}

	if (game->physics->negXHit){
		xSpeed = xSpeed * -1;
	}

	if (game->physics->posXHit){
		xSpeed = xSpeed * -1;
	}

}