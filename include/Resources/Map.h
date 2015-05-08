#include <vector>

class Model;

class Map{

public:


	Map();
	bool createMap();
	bool generateRandomMap();
	void drawBlocks();

	const int mapSize = 10;

	std::vector<Model*> blocks;

};