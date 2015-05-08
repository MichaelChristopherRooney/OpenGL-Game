#define STB_IMAGE_IMPLEMENTATION
#include <Resources\Game.h>
#include <Resources\objloader.hpp>

Model::Model(){

	// initialise to identity matrices
	translationMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);

	tx, ty, tz = 0.0f;

	isRotating = false;

	/* for now assume these values are the same for each model */
	specular = glm::vec3(1.0, 1.0, 1.0);
	diffuse = glm::vec3(1.0, 0.5, 0.0);
	ambient = glm::vec3(1.0, 1.0, 1.0);
	exponent = 100.0f;

	angle = 0.0f;

}

bool Model::setTexture(std::string textureFile){

	texture = new Texture();
	texture->load_from_file("Assets/Textures/metal.jpg");

	return true;

}

bool Model::setTexture(Texture *copyTexture){

	texture = copyTexture;

	return true;

}

void Model::findEdges(){

	hyo = lyo = 0;
	hzo = lzo = 0;
	hxo = lxo = 0;

	for (int i = 0; i < vertices.size(); i++){

		// find max and min y
		if (vertices[i].x > hyo){
			hyo = vertices[i].x;
		}

		if (vertices[i].x < lyo){
			lyo = vertices[i].x;
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

void Model::setRotating(float speed){
	isRotating = true;
	rotateRate = speed;
}

bool Model::initFromFile(std::string file){

	if (!loadOBJ(file.c_str(), vertices, uvs, normals)){
		return false;
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &uvVBO);
	glGenBuffers(1, &vnVBO);

	vaoSize = vertices.size() * sizeof(glm::vec3);
	uvSize = uvs.size() * sizeof(glm::vec2);
	normalSize = normals.size() * sizeof(glm::vec3);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vaoSize, &vertices[0], GL_STATIC_DRAW);

	findEdges();

	return true;

}

bool Model::copyFromExisting(Model *e){
	
	vertices = e->vertices;
	uvs = e->uvs;
	normals = e->normals;

	vaoSize = e->vaoSize;
	uvSize = e->uvSize;

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
	glBufferData(GL_ARRAY_BUFFER, vaoSize, &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	
	texture->set_active();

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

void Model::scale(float x, float y, float z){
	scaleMatrix = glm::scale(glm::vec3(x, y, z));
}

void Model::rotate(float deltaTime){

	angle += rotateRate * deltaTime;

	if (angle > 360.0){
		angle = angle - 360;
	}

	rotationMatrix = { cos(angle), 0, sin(angle), 0,
		0, 1, 0, 0,
		-sin(angle), 0, cos(angle), 0,
		0, 0, 0, 1

	};

}