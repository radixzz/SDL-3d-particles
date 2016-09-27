#include "SpriteRenderer.h"

namespace sax {

	SpriteRenderer::SpriteRenderer() {
		initVertexQuad();
		initDefaultShader();
	}

	SpriteRenderer::~SpriteRenderer() {
		glDeleteVertexArrays( 1, &this->quadVAO );
	}

	void SpriteRenderer::render( Sprite* sprite ) {
		defaultShader->use();
		glm::mat4 model;
		model = glm::translate( model, glm::vec3( sprite->position, 0.0f ) );
		model = glm::translate( model, glm::vec3( 0.5f * sprite->width, 0.5 * sprite->height, 0.0f ) );
		model = glm::rotate( model, sprite->rotation, glm::vec3( 0.0f, 0.0f, 1.0f ) );
		model = glm::translate( model, glm::vec3( -0.5f * sprite->width, -0.5 * sprite->height, 0.0f ) );
		model = glm::scale( model, glm::vec3( sprite->width, sprite->height, 1.0f ) );
		defaultShader->setMatrix4( "model", model );
		defaultShader->setVector3f( "color", glm::vec3( 1.0f, 1.0f, 1.0f ) );
		
		glEnableVertexAttribArray( defaultShader->getAttr( "a_position" ) );
		glEnableVertexAttribArray( defaultShader->getAttr( "a_texCoord" ) );
		
		sprite->onTextureDraw( std::bind( &SpriteRenderer::draw, this, std::placeholders::_1 ) );
		glBindVertexArray( this->quadVAO );
		glDrawArrays( GL_TRIANGLES, 0, 6 );
		glBindVertexArray( 0 );
		
		glDisableVertexAttribArray( defaultShader->getAttr( "a_position" ) );
		glDisableVertexAttribArray( defaultShader->getAttr( "a_texCoord" ) );
	}

	void SpriteRenderer::draw( Texture* texture ) {
		texture->bind();
		defaultShader->setInteger( "s_texture", 0 );

		//texture->unbind();
	}

	void SpriteRenderer::initDefaultShader() {
		std::string vs = Resources::getFileContents( "res/glsl/sprite_vs.glsl" );
		std::string fs = Resources::getFileContents( "res/glsl/sprite_fs.glsl" );
		defaultShader = Resources::get_shader( "sprite", vs, fs );
	}

	void SpriteRenderer::initVertexQuad() {

		GLuint VBO;
		GLfloat vertices[] = {
			// [Pos]	[Tex]
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,

			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f
		};

		glGenBuffers( 1, &VBO );
		glGenVertexArrays( 1, &this->quadVAO );

		glBindBuffer( GL_ARRAY_BUFFER, VBO );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
		glBindVertexArray( this->quadVAO );
		glEnableVertexAttribArray( 0 );
		glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof( GL_FLOAT ), ( GLvoid* ) 0 );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		glBindVertexArray( 0 );

	}

}