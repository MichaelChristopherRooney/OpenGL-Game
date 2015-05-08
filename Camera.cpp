#include <Resources\Game.h>

Camera::Camera(){

	up = glm::vec3(0, 1, 0);
	position = glm::vec3(2, 0.5, 0);
	jump = glm::vec3(0, 1, 0);

	fov = 90.0f;

	projection = glm::perspective(fov, (float)game->xRes / game->yRes, 0.1f, 100.0f);

	horizontalAngle = 3.14f;
	verticalAngle = 0.0f;

	right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

}


void Camera::update(){

	view = glm::lookAt(
		glm::vec3(
			2,
			game->player->playerModel->yLen + game->player->playerModel->maxY,
			game->player->playerModel->minZ + game->player->playerModel->zLen / 2
		),
		game->player->playerModel->centre,
		up
	);
	
	glUniformMatrix4fv(game->shader->shaderIDs.at("projection"), 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(game->shader->shaderIDs.at("view"), 1, GL_FALSE, &view[0][0]);

}

void Camera::calculateAngles(){

	horizontalAngle += mouseSpeed * game->deltaTime * float((game->xRes / 2) - game->input->mouseX);
	verticalAngle += mouseSpeed * game->deltaTime * float((game->yRes / 2) - game->input->mouseY);

	if (verticalAngle > maxVertical){
		verticalAngle = maxVertical;
	}else if (verticalAngle < minVertical){
		verticalAngle = minVertical;
	}

}

void Camera::calculatePosition(){

	if (game->input->keys.at("W")){
		position += direction * game->deltaTime * cameraSpeed;
	}

	if (game->input->keys.at("A")){
		position -= right * game->deltaTime * cameraSpeed;
	}

	if (game->input->keys.at("S")){
		position -= direction * game->deltaTime * cameraSpeed;
	}

	if (game->input->keys.at("D")){
		position += right * game->deltaTime * cameraSpeed;
	}

}

void Camera::calculateMatrices(){

	/*
	direction = glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	*/

	/*
	right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);
	*/
	//up = glm::cross(right, direction);

	view = glm::lookAt(
		position,
		game->player->playerModel->centre,
		up
	);

}