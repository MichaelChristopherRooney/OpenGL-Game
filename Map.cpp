#include <Resources\Game.h>
#include <cstdlib>

Map::Map(){
	createMap();
}

void Map::createMap(){

	Model *temp;

	// create the floor
	for (int i = 0; i < mapSize; i++){
		for (int j = 0; j < mapSize; j++){
			temp = new Model();
			temp->copyFromExisting(game->models->cube);
			temp->setTexture(game->textures->metalTexture);
			temp->translate(temp->xLen * i, -temp->yLen / 2, temp->zLen * j);
			floorBlocks.push_back(temp);
		}
	}

	// create the back edge
	for (int i = 0; i < mapSize; i++){
		temp = new Model();
		temp->copyFromExisting(game->models->cube);
		temp->setTexture(game->textures->metalTexture);
		temp->translate(temp->xLen * -1, temp->yLen / 2, temp->zLen * i);
		wallBlocks.push_back(temp);
	}

	// create the left edge
	for (int i = 0; i < mapSize; i++){
		temp = new Model();
		temp->copyFromExisting(game->models->cube);
		temp->setTexture(game->textures->metalTexture);
		temp->translate(temp->xLen * i, temp->yLen / 2, temp->zLen * -1);
		wallBlocks.push_back(temp);
	}

	// create the right edge
	for (int i = 0; i < mapSize; i++){
		temp = new Model();
		temp->copyFromExisting(game->models->cube);
		temp->setTexture(game->textures->metalTexture);
		temp->translate(temp->xLen * i, temp->yLen / 2, temp->zLen * mapSize);
		wallBlocks.push_back(temp);
	}

	// create the front edge
	for (int i = 0; i < mapSize; i++){
		temp = new Model();
		temp->copyFromExisting(game->models->cube);
		temp->setTexture(game->textures->metalTexture);
		temp->translate(temp->xLen * mapSize, temp->yLen / 2, temp->zLen * i);
		wallBlocks.push_back(temp);
	}

}

void Map::drawBlocks(){

	for (int i = 0; i < wallBlocks.size(); i++){
		wallBlocks.at(i)->draw();
	}

	for (int i = 0; i < floorBlocks.size(); i++){
		floorBlocks.at(i)->draw();
	}

}