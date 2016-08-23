
attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 color;

varying Color;
varying TexCoord;

void main() {
	
	Color = TexCoord;
	gl_Position = vec4( Position, 1.0f );
	TexCoord = vec2( texCoord.x, 1.0 - texCoord.y );
	
}