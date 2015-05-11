class Game;
class Model;
extern Game *game; 

class Player{

public:

	Player();

	void draw();
	void update();
	void handleInput();
	void handlePhysics();

	Model *playerModel;

	float xSpeed;
	float zSpeed;

	const float acceleration = 0.025f;
	const float maxSpeed = 1.0f;


};