#include <Resources\Game.h>

Camera::Camera(){

	fov = 90.0f;

	projection = glm::perspective(fov, (float)game->xRes / game->yRes, 0.1f, 100.0f);

	horizontalAngle = 3.141f;
	verticalAngle = 0.7f;

}

void Camera::updateAngles(){

	
	horizontalAngle += mouseSpeed * game->deltaTime * float((game->xRes / 2) - game->input->mouseX);
	verticalAngle += mouseSpeed * game->deltaTime * double((game->yRes / 2) - game->input->mouseY);

	if (verticalAngle > maxVertical){
		verticalAngle = maxVertical;
	}else if (verticalAngle < minVertical){
		verticalAngle = minVertical;
	}

	direction = glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle) * 2,
		sin(verticalAngle)  * 2,
		cos(verticalAngle) * cos(horizontalAngle) * 2
	);

	right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	up = glm::cross(right, direction);

}

void Camera::updatePosition(){

	view = glm::lookAt(
		direction + game->player->playerModel->centre,
		game->player->playerModel->centre,
		up
	);

	glUniformMatrix4fv(game->shader->shaderIDs.at("projection"), 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(game->shader->shaderIDs.at("view"), 1, GL_FALSE, &view[0][0]);

}