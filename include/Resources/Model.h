#include <gl\glew.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <string>
#include <vector>

class Texture;

class Game;
extern Game* game;

class Model{

public:

	Model();

	Texture *texture;


	bool initFromFile(std::string file);
	bool copyFromExisting(Model *e);
	bool setTexture(std::string textureFile);
	bool setTexture(Texture *copyTexture);
	

	void findEdges();
	void setRotating(float speed);
	void translate(float x, float y, float z);
	void translate(glm::vec3 t);
	void translate();
	void scale(float x, float y, float z);
	void rotate(float deltaTime);
	void draw();

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	GLuint vao;
	GLuint vbo;

	GLuint uvVBO;
	GLuint vnVBO;

	int vaoSize;
	int uvSize;
	int normalSize;

	bool isRotating;
	float rotateRate;
	float angle;

	float speed = 0;
	float acceleration = 0;

	float tx, ty, tz;
	glm::vec3 tVec;

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