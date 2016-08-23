uniform sampler2D texture;
varying Color;
varying TexCoord;

void main() {
	gl_FragColor = texture2D( texture, texCoord );
}