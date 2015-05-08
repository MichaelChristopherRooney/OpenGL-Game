#version 400

layout(location = 0) in vec3 vertexPoints;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

out vec2 UV;
out vec3 eyePosition;
out vec3 eyeNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

void main () {

	eyePosition = vec3(view * model * translation * rotation * scale * vec4(vertexPoints, 1.0));
	eyeNormal = vec3(view * model * translation * rotation * vec4(vertexNormal, 0.0));
	gl_Position = projection * vec4(eyePosition, 1.0);
	UV = vertexUV;
	
}