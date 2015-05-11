#include <string>
#include <stdio.h>
#include <gl/glew.h>
#include <fstream>
#include <unordered_map>

class Shader{

public:

	Shader();
	bool createShader();
	void getIDs();
	bool createVertexShader();
	bool createFragmentShader();
	bool Shader::loadShaderFile(std::string& loadedString, std::string& fileToLoad);
	void setActive();
	bool checkShaderStatus();

	std::unordered_map<std::string, GLuint> shaderIDs;

	std::string vertexFilePath = "Assets/Shaders/vertexshader.glsl";
	std::string fragmentFilePath = "Assets/Shaders/fragmentshader.glsl";

	GLuint vs, fs;
	GLuint shaderProgramme;

};