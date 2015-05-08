/*
This is an object intended to hold all models that are to be used in the game
This is to allow data to be shared so that redundant copies do not have to be made/loaded
*/

#include <string>

class Model;

class ModelData{

public:

	ModelData();

	Model *cube;

	const std::string cubeFile = "Assets/Models/cube.obj";

};