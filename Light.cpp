#include <Resources\Game.h>

Light::Light(){

	lightPosition = glm::vec3(1, 0, 1);
	lightSpecular = glm::vec3(1.0, 1.0, 1.0);
	lightDiffuse = glm::vec3(0.7, 0.7, 0.7);
	lightAmbient = glm::vec3(0.2, 0.2, 0.2);

}

void Light::setActive(){
	
}

void Light::update(){

	glUniform3fv(game->shader->shaderIDs.at("lightPosition"), 1, &lightPosition[0]);
	glUniform3fv(game->shader->shaderIDs.at("lightSpecular"), 1, &lightSpecular[0]);
	glUniform3fv(game->shader->shaderIDs.at("lightDiffuse"), 1, &lightDiffuse[0]);
	glUniform3fv(game->shader->shaderIDs.at("lightAmbient"), 1, &lightAmbient[0]);

	lightPosition = glm::vec3(
		2,
		(game->player->playerModel->yLen * 3) + game->player->playerModel->maxY,
		game->player->playerModel->minZ + game->player->playerModel->zLen / 2
	);

}