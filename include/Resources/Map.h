#include <vector>

class Model;

class Map{

public:

	Map();
	void createMap();
	void drawBlocks();

	const int mapSize = 10;

	std::vector<Model*> floorBlocks;
	std::vector<Model*> wallBlocks;

};