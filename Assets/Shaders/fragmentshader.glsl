#version 400

in vec2 UV;

out vec3 colour;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 rotation;

uniform sampler2D sampler;

void main () {
	colour = texture2D(sampler, UV).rgb;
}