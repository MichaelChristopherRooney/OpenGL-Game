#include <Resources\Game.h>
#include <cstdlib>

Map::Map(){

}

bool Map::createMap(){

	Model *temp;

	// create the floor
	for (int i = 0; i < mapSize; i++){
		for (int j = 0; j < mapSize; j++){
			temp = new Model();
			temp->copyFromExisting(game->models->cube);
			temp->setTexture(game->textures->metalTexture);
			temp->translate(temp->xLen * i, 0, temp->zLen * j);
			blocks.push_back(temp);
		}
	}

	// create the back edge
	for (int i = 0; i < mapSize; i++){
		temp = new Model();
		temp->copyFromExisting(game->models->cube);
		temp->setTexture(game->textures->metalTexture);
		temp->translate(temp->xLen * -1, temp->yLen, temp->zLen * i);
		blocks.push_back(temp);
	}

	// create the left edge
	for (int i = 0; i < mapSize; i++){
		temp = new Model();
		temp->copyFromExisting(game->models->cube);
		temp->setTexture(game->textures->metalTexture);
		temp->translate(temp->xLen * i, temp->yLen, temp->zLen * -1);
		blocks.push_back(temp);
	}

	// create the right edge
	for (int i = 0; i < mapSize; i++){
		temp = new Model();
		temp->copyFromExisting(game->models->cube);
		temp->setTexture(game->textures->metalTexture);
		temp->translate(temp->xLen * i, temp->yLen, temp->zLen * mapSize);
		blocks.push_back(temp);
	}

	// create the front edge
	for (int i = 0; i < mapSize; i++){
		temp = new Model();
		temp->copyFromExisting(game->models->cube);
		temp->setTexture(game->textures->metalTexture);
		temp->translate(temp->xLen * mapSize, temp->yLen, temp->zLen * i);
		blocks.push_back(temp);
	}

	return true;

}

void Map::drawBlocks(){

	for (int i = 0; i < blocks.size(); i++){
		blocks.at(i)->draw();
	}

}