class Game;
class Model;
extern Game *game; 

class Player{

public:

	Player();

	void updateAndDraw();
	Model *playerModel;

	const float playerSpeed = 2.0f;


};