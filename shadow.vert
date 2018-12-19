#version 330

attribute vec4 position;

uniform mat4 persp_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;

void main() {
	vec4 P = model_matrix * position;
    gl_Position = persp_matrix * view_matrix * P;
}