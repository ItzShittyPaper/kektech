#version 330 core
out vec4 FragColor;

in vec3 VertexColor;
in vec2 TexCoord;

uniform sampler2D Texture;
uniform sampler2D Decal;

uniform float MixRatio;

void main() {
	FragColor = mix(texture(Texture, TexCoord), texture(Decal, TexCoord), MixRatio);
} 
