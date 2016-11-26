#version 120

uniform sampler2D s_texture;
uniform vec3 u_color;

varying vec2 v_texCoord;

void main() {
	gl_FragColor = vec4(u_color, 0.2) * texture2D( s_texture, v_texCoord );
}
