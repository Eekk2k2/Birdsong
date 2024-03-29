#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 vp; // projection * view

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;


void main() {
	gl_Position = vp * model * vec4(aPos, 1.0);

    FragPos = vec3(model * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(model))) * aNormal;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}