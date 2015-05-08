/*
This is an object intended to hold all textures that are to be used in the game
This is to allow data to be shared so that redundant copies do not have to be made/loaded
*/

#include <string>

class Texture;

class TextureData{

public:

	TextureData();

	Texture *metalTexture;

	const std::string metalTextureFile = "Assets/Textures/metal.jpg";

};