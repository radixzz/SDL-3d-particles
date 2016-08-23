#ifndef SAX_SPRITE_RENDERER_H
#define SAX_SPRITE_RENDERER_H

#include <GL\glew.h>
#include <SDL.h>

#include "Sprite.h"
#include "Shader.h"
#include "Resources.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

namespace sax {
	class SpriteRenderer {
		public:
			SpriteRenderer();
			~SpriteRenderer();
			//void render( Sprite* sprite );
		private:
			void initDefaultShader();
			void initVertexQuad();
			GLuint quadVAO;
			Shader* defaultShader;
	};
}

#endif
