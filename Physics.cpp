#include <Resources\Game.h>

Physics::Physics(){
	
}

void Physics::checkForHit(){

	posXHit = negXHit = posZHit = negZHit = false;

	glm::vec3 centre = game->player->playerModel->centre;
	float radius = game->player->playerModel->xLen / 2;

	float pMaxZ = game->player->playerModel->maxZ;
	float pMinZ = game->player->playerModel->minZ;

	float pMaxX = game->player->playerModel->maxX;
	float pMinX = game->player->playerModel->minX;

	for (int i = 0; i < game->map->wallBlocks.size(); i++){

		cur = game->map->wallBlocks.at(i);

		// check if the "back" of the player hits a block
		if (pMinZ >= cur->minZ && pMinZ <= cur->maxZ){
			if (centre.x >= cur->minX && centre.x <= cur->maxX){
				negZHit = true;
			}
		}

		// check if the "front" of the player hits a block
		if (pMaxZ >= cur->minZ && pMaxZ <= cur->maxZ){
			if (centre.x >= cur->minX && centre.x <= cur->maxX){
				posZHit = true;
			}
		}

		// check if the "left side" of the player hits a block
		if (pMinX >= cur->minX && pMinX <= cur->maxX){
			if (centre.z >= cur->minZ && centre.z <= cur->maxZ){
				negXHit = true;
			}
		}

		// check if the "right side" of the player hits a block
		if (pMaxX >= cur->minX && pMaxX <= cur->maxX){
			if (centre.z >= cur->minZ && centre.z <= cur->maxZ){
				posXHit = true;
			}
		}
		
	}

}