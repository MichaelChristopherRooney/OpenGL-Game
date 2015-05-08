#include <vector>

class Model;

class Map{

public:


	Map();
	bool createMap();
	void drawBlocks();

	const int mapSize = 10;

	std::vector<Model*> blocks;

};