#include <string>
#include <gl\glew.h>
#include <Resources\stb_image.h>

class Texture{

public:

	Texture();

	void setActive();
	bool loadFromFile(std::string file);

	int width, height, comp;
	unsigned char * data;
	GLuint textureID;

};