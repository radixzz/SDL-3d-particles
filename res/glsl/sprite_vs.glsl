#version 120

attribute vec4 a_vertex;
attribute vec3 a_color;

uniform mat4 u_model;
uniform mat4 u_projection;

varying vec2 v_texCoord;

void main() {
	v_texCoord = a_vertex.zw;
	gl_Position = u_projection * u_model * vec4( a_vertex.xy, 0.0, 1.0 );
}
