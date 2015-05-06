#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Game;
extern Game *game;

class Input{

public:

	Input();
	void update();
	std::unordered_map<std::string, bool> keys;

	double mouseX;
	double mouseY;

};