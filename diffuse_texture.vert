#version 330

attribute vec4 position;
attribute vec4 normal;
attribute vec2 texture_coord;

uniform mat4 persp_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform mat4 normal_matrix;
uniform vec4 light_position;

uniform mat4 std2unit_matrix;
uniform mat4 light_view_matrix;

out vec4 vshadow_position;

out vec4 normal_vector;
out vec4 light_vector;
out vec2 vtexture_coord;

void main() {
  vec4 P = model_matrix * position;

  gl_Position = persp_matrix * view_matrix * P;

  vshadow_position = persp_matrix * light_view_matrix * P;

  normal_vector = normal_matrix * normal;
  light_vector = light_position - P;
  vtexture_coord = texture_coord;
}

