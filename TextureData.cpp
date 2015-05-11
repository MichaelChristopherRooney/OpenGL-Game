/*
This is an object intended to hold all textures that are to be used in the game
This is to allow data to be shared so that redundant copies do not have to be made/loaded
*/

#include <Resources\Game.h>

TextureData::TextureData(){

	metalTexture = new Texture();
	metalTexture->loadFromFile(metalTextureFile);


}