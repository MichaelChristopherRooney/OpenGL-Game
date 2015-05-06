#include <Resources\Texture.h>

Texture::Texture(){

}

void Texture::load_from_file(std::string file){
	data = stbi_load(file.c_str(), &width, &height, &comp, 0);
	glGenTextures(1, &textureID);
}

void Texture::set_active(){

	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

}