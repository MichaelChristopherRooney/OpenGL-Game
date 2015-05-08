#version 400

in vec2 UV;
in vec3 eyePosition;
in vec3 eyeNormal;

out vec4 colour;

uniform mat4 view;

uniform sampler2D sampler;

uniform vec3 lightPosition;
uniform vec3 lightSpecular;
uniform vec3 lightDiffuse;
uniform vec3 lightAmbient;

vec3 surfaceSpecular = vec3(1.0, 1.0, 1.0);
vec3 surfaceDiffuse = vec3(1.0, 0.5, 0.0);
vec3 surfaceAmbient = vec3(1.0, 1.0, 1.0);
float specularExponent = 100.0;

void main () {

	vec3 lightEyePosition = vec3(view * vec4(lightPosition, 1.0));
	vec3 distance = lightEyePosition - eyePosition;
	vec3 direction = normalize(distance);
	
	vec3 diffuseIntensity = lightDiffuse * surfaceDiffuse * max(dot(direction, eyeNormal), 0.0);
	
	vec3 ambientIntensity = lightAmbient * surfaceAmbient;

	vec3 surfaceEyeDirection = normalize(-eyePosition);
	float specularFactor = pow(max(dot
							(normalize(surfaceEyeDirection + direction), eyeNormal), 
							0.0), specularExponent);
	vec3 specularIntensity = lightSpecular * surfaceSpecular * specularFactor;

	
	colour = texture2D(sampler, UV) * vec4(specularIntensity + diffuseIntensity + ambientIntensity, 1.0);
}