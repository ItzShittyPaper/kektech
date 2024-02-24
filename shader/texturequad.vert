#version 330 core
layout (location = 0) in vec3 VertexPos3D;
layout (location = 1) in vec3 VertexColor3D;
layout (location = 2) in vec2 TexCoord2D;

out vec3 VertexColor;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 TransformMatrix;

void main() {
    gl_Position = projection * view * model * TransformMatrix * vec4(VertexPos3D, 1.0f);
    VertexColor = VertexColor3D;
    TexCoord = TexCoord2D;
}
