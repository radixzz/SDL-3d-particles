#ifndef SAX_SPRITE_RENDERER_H
#define SAX_SPRITE_RENDERER_H

#include <GL/glew.h>
#include <SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Sprite.h"
#include "Shader.h"
#include "Resources.h"

namespace sax {
	class SpriteRenderer {
		public:
			SpriteRenderer();
			~SpriteRenderer();
			void render( Sprite* sprite );
		private:
			void draw( Texture* texture );
			void initDefaultShader();
			void initVertexQuad();
			GLuint quadVAO;
			Shader* defaultShader;
	};
}

#endif
