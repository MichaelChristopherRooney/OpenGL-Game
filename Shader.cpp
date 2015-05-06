#include <Resources/Shader.h>

Shader::Shader(){

}

bool Shader::createShader(){

	/* load the vertex shader */
	if (!createVertexShader()){
		return false;
	}

	/* load the fragment shader */
	if (!createFragmentShader()){
		return false;
	}

	if (!checkShaderStatus()){
		return false;
	}

	shaderProgramme = glCreateProgram();
	glAttachShader(shaderProgramme, fs);
	glAttachShader(shaderProgramme, vs);
	glLinkProgram(shaderProgramme);

	getIDs();

	return true;

}

bool Shader::createVertexShader(){

	std::string loadedString;
	const char* shaderString;

	if (!loadShaderFile(loadedString, vertexFilePath)){
		return false;
	}

	shaderString = loadedString.c_str();
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &shaderString, NULL);
	glCompileShader(vs);

}

bool Shader::createFragmentShader(){

	std::string loadedString;
	const char* shaderString;

	if (!loadShaderFile(loadedString, fragmentFilePath)){
		return false;
	}

	shaderString = loadedString.c_str();
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &shaderString, NULL);
	glCompileShader(fs);

}

bool Shader::checkShaderStatus(){

	GLint status;

	glGetShaderiv(vs, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE){

		char buffer[512];
		glGetShaderInfoLog(vs, 512, NULL, buffer);
		printf("%s:\n %s\n", "Vertex shader:", buffer);

		return false;

	}

	glGetShaderiv(fs, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE){

		char buffer[512];
		glGetShaderInfoLog(fs, 512, NULL, buffer);
		printf("%s:\n %s\n", "Fragment shader:", buffer);

		return false;

	}

	return true;

}

void Shader::getIDs(){

	shaderIDs.insert({
		{ "model",			glGetUniformLocation(shaderProgramme, "model"			) },
		{ "projection",		glGetUniformLocation(shaderProgramme, "projection"		) },
		{ "view",			glGetUniformLocation(shaderProgramme, "view"			) },
		{ "translation",	glGetUniformLocation(shaderProgramme, "translation"		) },
		{ "rotation",		glGetUniformLocation(shaderProgramme, "rotation"		) },
		{ "scale",			glGetUniformLocation(shaderProgramme, "scale"			) },

	});

	/*
			{ "lightPosition",	glGetUniformLocation(shaderProgramme, "lightPosition"	) },
		{ "lightSpecular",	glGetUniformLocation(shaderProgramme, "lightSpecular"	) },
		{ "lightDiffuse",	glGetUniformLocation(shaderProgramme, "lightDiffuse"	) },
		{ "lightAmbient",	glGetUniformLocation(shaderProgramme, "lightAmbient"	) }
	*/

}

bool Shader::loadShaderFile(std::string& loadedString, std::string& fileToLoad){

	std::ifstream input(fileToLoad, std::ios::in);

	if (input.is_open() && input.good() && !input.bad()){
		loadedString.assign((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
		input.close();
		input.clear();
		return true;
	}
	else{
		printf("Error opening the file\n");
		return false;
	}


}

void Shader::setActive(){
	glUseProgram(shaderProgramme);
}