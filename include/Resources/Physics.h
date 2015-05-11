class Game;
extern Game *game;

class Physics{

public:

	Physics();

	void checkForHit();

	bool posXHit;
	bool negXHit;
	bool posZHit;
	bool negZHit;

	Model *cur;

};