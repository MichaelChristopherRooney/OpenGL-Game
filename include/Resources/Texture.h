#include <string>
#include <gl\glew.h>
#include <Resources\stb_image.h>

class Texture{

public:

	Texture();

	void set_active();
	void load_from_file(std::string file);

	int width, height, comp;
	unsigned char * data;
	GLuint textureID;

};