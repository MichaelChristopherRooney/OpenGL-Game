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

		if (i == 0 || i == mapSize - 1){
			localHeight = 1;
		}else{
			if (localHeight == 0){
				localHeight = (rand() % 3) + 1;
			}else{ // don't allow two sequential empty spaces
				localHeight = rand() % 4;
			}
			
		}

		for (int n = 0; n < localHeight; n++){
			temp = new Model();
			temp->initFromFile("Assets/Models/cube.obj");
			temp->translate(0, temp->yLen * n, temp->zLen * -i);
			blocks.push_back(temp);
		}

	}

	return true;

}

void Map::drawBlocks(){

	for (int i = 0; i < blocks.size(); i++){
		blocks.at(i)->draw();
	}

}