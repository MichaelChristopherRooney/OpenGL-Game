#include <gl\glew.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <string>

class Texture;

class Game;
extern Game* game;

class Model{

public:

	Model();

	Texture *texture;

	bool initFromFile(std::string file);

	void findEdges();
	void setRotating(float speed);
	void translate(float x, float y, float z);
	void translate(glm::vec3 t);
	void translate();
	void scale(float x, float y, float z);
	void rotate(float deltaTime);
	void draw();

	GLfloat* vp = NULL;
	GLfloat* vn = NULL;
	GLfloat* UV = NULL;
	int pointCount = 0;

	GLfloat uvSize;

	bool isRotating;
	float rotateRate;
	float angle;

	float speed = 0;
	float acceleration = 0;

	float tx, ty, tz;
	glm::vec3 tVec;

	GLuint vao;
	GLuint vbo;
	GLuint colourVBO;

	GLuint uvVBO;
	GLuint vnVBO;

	int vaoSize;

	float hxo;
	float lxo;
	float hyo;
	float lyo;
	float hzo;
	float lzo;

	float minX;
	float maxX;
	float minY;
	float maxY;
	float minZ;
	float maxZ;

	glm::vec3 centre;

	float xLen;
	float yLen;
	float zLen;
	float maxLen;

	glm::mat4 translationMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 rotationMatrix;

	/* for now assume these values are the same for each model */
	glm::vec3 specular;
	glm::vec3 diffuse;
	glm::vec3 ambient;
	float exponent;

};