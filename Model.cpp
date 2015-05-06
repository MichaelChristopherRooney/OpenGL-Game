#define STB_IMAGE_IMPLEMENTATION
#include <Resources\Texture.h>
#include <Resources\Game.h>
#include <Resources\obj_parser.h>

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

	texture = new Texture();
	texture->load_from_file("Assets/Textures/metal.jpg");

}

void Model::findEdges(){

	hyo = lyo = vp[1];
	hzo = lzo = vp[2];
	hxo = lxo = vp[3];

	for (int i = 0; i < pointCount; i += 3){

		// find max and min y
		if (vp[i + 1] > hyo){
			hyo = vp[i + 1];
		}

		if (vp[i + 1] < lyo){
			lyo = vp[i + 1];
		}

		// find max and min z
		if (vp[i + 2] > hzo){
			hzo = vp[i + 2];
		}

		if (vp[i + 2] < lzo){
			lzo = vp[i + 2];
		}

		// find max and min x
		if (vp[i + 3] > hxo){
			hxo = vp[i + 3];
		}

		if (vp[i + 3] < lzo){
			lxo = vp[i + 3];
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

	if (!load_obj_file(file.c_str(), vp, UV, vn, pointCount)){
		printf("Error loading model");
		return false;
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &uvVBO);
	glGenBuffers(1, &vnVBO);

	vaoSize = sizeof(float) * pointCount * 3;
	uvSize = sizeof(UV) * sizeof(float) * pointCount;

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vaoSize, vp, GL_STATIC_DRAW);

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
	glBufferData(GL_ARRAY_BUFFER, uvSize, UV, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	
	/* set normal data in the shader */
	glBindBuffer(GL_ARRAY_BUFFER, vnVBO);
	glBufferData(GL_ARRAY_BUFFER, vaoSize, vn, GL_STATIC_DRAW);
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