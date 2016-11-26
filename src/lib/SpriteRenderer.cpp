#include "SpriteRenderer.h"

namespace sax {

	SpriteRenderer::SpriteRenderer() {
		initVertexQuad();
		initDefaultShader();
		resize( 0, 0 );
	}

	SpriteRenderer::~SpriteRenderer() {
		glDeleteVertexArrays( 1, &this->quadVAO );
	}

	void SpriteRenderer::resize( int width, int height ) {
		this->width = width;
		this->height = height;
		MVP = glm::ortho(0.0, (double)width, (double)height, 0.0, -1.0, 1.0);
		defaultShader->use().setMatrix4( "u_projection", MVP );
	}

	void SpriteRenderer::render( Sprite* sprite ) {
		defaultShader->use();
		
		glm::mat4 model;
		model = glm::translate( model, glm::vec3( sprite->position, 0.0f ) );
		model = glm::translate( model, glm::vec3( 0.5 * sprite->width, 0.5 * sprite->height, 0.0f ) );
		model = glm::rotate( model, sprite->rotation, glm::vec3( 0.0f, 0.0f, 1.0f ) );
		model = glm::translate( model, glm::vec3( -0.5f * sprite->width, -0.5 * sprite->height, 0.0f ) );
		model = glm::scale( model, glm::vec3( sprite->width, sprite->height, 1.0f ) );
		defaultShader->setMatrix4( "u_model", model );
		defaultShader->setVector3f( "u_color", sprite->color );
		 
		//defaultShader->setVector3f( "color", glm::vec3( 1.0f, 1.0f, 1.0f ) );
		glEnableVertexAttribArray( defaultShader->getAttr( "a_vertex" ) );
		
		sprite->onTextureDraw( std::bind( &SpriteRenderer::draw, this, std::placeholders::_1 ) );
		
		
		//glDisableVertexAttribArray( defaultShader->getAttr( "a_vertex" ) );
	}

	void SpriteRenderer::draw( Texture* texture ) {
		texture->bind();
		defaultShader->setInteger( "s_texture", 0 );
		glBindVertexArray( this->quadVAO );
		glDrawArrays( GL_TRIANGLES, 0, 6 );
		glBindVertexArray( 0 );
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

		glGenVertexArrays( 1, &this->quadVAO );
		glGenBuffers( 1, &VBO );
		
		glBindBuffer( GL_ARRAY_BUFFER, VBO );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
		
		glBindVertexArray( this->quadVAO );
		glEnableVertexAttribArray( 0 );
		glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof( GL_FLOAT ), ( GLvoid* ) 0 );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		glBindVertexArray( 0 );

	}

}