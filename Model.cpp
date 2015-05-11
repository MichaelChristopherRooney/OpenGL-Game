#define STB_IMAGE_IMPLEMENTATION
#include <Resources\Game.h>
#include <Resources\objloader.hpp>

Model::Model(){

	// initialise to identity matrices
	translationMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);

	tx, ty, tz = 0.0f; // model is not initially translated

	// for now assume these values are the same for each model
	specular = glm::vec3(1.0, 1.0, 1.0);
	diffuse = glm::vec3(1.0, 1.0, 1.0);
	ambient = glm::vec3(1.0, 1.0, 1.0);
	exponent = 100.0f;

}

bool Model::setTexture(std::string textureFile){

	texture = new Texture();

	if (!texture->loadFromFile(textureFile)){
		return false;
	}

	return true;

}

bool Model::setTexture(Texture *copyTexture){

	if (copyTexture == NULL){
		printf("Error: Texture to copy does not exist\n");	
		return false;
	}

	texture = copyTexture;

}

/*
this functions finds the
	- length of the model across each axis
	- the max and min points in each axis
these are used in transformations and collision detection
*/
void Model::findEdges(){

	// these hold the original values before transformations
	hyo = lyo = 0;
	hzo = lzo = 0;
	hxo = lxo = 0;

	for (int i = 0; i < vertices.size(); i++){

		// find max and min y
		if (vertices[i].y > hyo){
			hyo = vertices[i].y;
		}

		if (vertices[i].y < lyo){
			lyo = vertices[i].y;
		}

		// find max and min z
		if (vertices[i].z > hzo){
			hzo = vertices[i].z;
		}

		if (vertices[i].z < lzo){
			lzo = vertices[i].z;
		}

		// find max and min x
		if (vertices[i].x > hxo){
			hxo = vertices[i].x;
		}

		if (vertices[i].x < lzo){
			lxo = vertices[i].x;
		}

	}

	xLen = hxo - lxo;
	yLen = hyo - lyo;
	zLen = hzo - lzo;

	// initialise to the original values

	maxX = hxo;
	minX = lxo;

	maxY = hyo;
	minY = lyo;

	maxZ = hzo;
	minZ = lzo;

	centre = glm::vec3(
		minX + (xLen / 2),
		minY + (yLen / 2),
		minZ + (zLen / 2)
	);

}

bool Model::initFromFile(std::string file){

	if (!loadOBJ(file.c_str(), vertices, uvs, normals)){
		printf("Error: Cannot load model\n");
		return false;
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &uvVBO);
	glGenBuffers(1, &vnVBO);

	vaoSize = vertices.size() * sizeof(glm::vec3);
	uvSize = uvs.size() * sizeof(glm::vec2);
	normalSize = normals.size() * sizeof(glm::vec3);
	printf("Normal: %d, UV: %d\n", uvSize, normalSize);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vaoSize, &vertices[0], GL_STATIC_DRAW);

	findEdges();

	return true;

}

bool Model::copyFromExisting(Model *e){
	
	if (e == NULL){
		printf("Error: Model to copy does not exist\n");
		return false;
	}

	vertices = e->vertices;
	uvs = e->uvs;
	normals = e->normals;

	vaoSize = e->vaoSize;
	uvSize = e->uvSize;
	normalSize = e->normalSize;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &uvVBO);
	glGenBuffers(1, &vnVBO);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vaoSize, &vertices[0], GL_STATIC_DRAW);

	findEdges();
	
	return true;

}

void Model::draw(){
	
	/* set matrix data in the shader */
	glUniformMatrix4fv(game->shader->shaderIDs.at("translation"), 1, GL_FALSE, &translationMatrix[0][0]);
	glUniformMatrix4fv(game->shader->shaderIDs.at("rotation"), 1, GL_FALSE, &rotationMatrix[0][0]);
	glUniformMatrix4fv(game->shader->shaderIDs.at("scale"), 1, GL_FALSE, &scaleMatrix[0][0]);
	
	glBindVertexArray(vao);

	/* set point data in the shader */
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	/* set uv data in the shader */
	glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
	glBufferData(GL_ARRAY_BUFFER, uvSize, &uvs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	
	/* set normal data in the shader */
	glBindBuffer(GL_ARRAY_BUFFER, vnVBO);
	glBufferData(GL_ARRAY_BUFFER, normalSize, &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	
	texture->setActive();

	glDrawArrays(GL_TRIANGLES, 0, vaoSize);

}

void Model::translate(float x, float y, float z){
	tx = x; ty = y; tz = z;
	Model::translate();
}

void Model::translate(glm::vec3 t){
	tx = t.x; ty = t.y; tz = t.z;
	Model::translate();
}

void Model::translate(){

	// recalculate edges
	maxX = hxo + tx; minX = lxo + tx;
	maxY = hyo + ty; minY = lyo + ty;
	maxZ = hzo + tz; minZ = lzo + tz;

	centre = glm::vec3(
		minX + (xLen / 2),
		minY + (yLen / 2),
		minZ + (zLen / 2)
	);

	tVec = glm::vec3(tx, ty, tz);
	translationMatrix = glm::translate(tVec);

}
