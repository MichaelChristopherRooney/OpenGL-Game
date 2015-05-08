#include <Resources\Game.h>
#include <cstdlib>

Map::Map(){

}

bool Map::createMap(){

	generateRandomMap();

	/*
	Model *temp;
	for (int i = 0; i < 10; i++){
		temp = new Model();
		temp->initFromFile("Assets/Models/cube.obj");
		temp->translate(0, -temp->yLen, temp->zLen * -i);
		blocks.push_back(temp);
	}
	*/
	return true;

}

bool Map::generateRandomMap(){

	int localHeight = 1;
	Model *temp;

	for (int i = 0; i < mapSize; i++){
		for (int j = 0; j < mapSize; j++){

			localHeight = (rand() % 2) + 1;

			for (int n = 0; n < localHeight; n++){
				temp = new Model();
				temp->copyFromExisting(game->models->cube);
				temp->setTexture(game->textures->metalTexture);
				temp->translate(temp->xLen * i, temp->yLen * n, temp->zLen * j);
				blocks.push_back(temp);
			}

		}
	}

	return true;

}

void Map::drawBlocks(){

	for (int i = 0; i < blocks.size(); i++){
		blocks.at(i)->draw();
	}

}