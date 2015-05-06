#version 400

layout(location = 0) in vec3 vertexPoints;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

out vec2 UV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 translation;
uniform mat4 rotation;

vec3 eyePosition;
vec3 eyeNormal;

void main () {

	eyePosition = vec3(view * model * translation * rotation * vec4(vertexPoints, 1.0));
	eyeNormal = vec3(view * model * rotation * vec4(vertexNormal, 0.0));
	gl_Position = projection * vec4(eyePosition, 1.0);
	UV = vertexUV;
	
}