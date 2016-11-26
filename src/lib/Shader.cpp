#include "Shader.h"
#include "Resources.h"
#include "Log.h"

namespace sax {

	Shader::Shader(): program( 0 ), compilation_succeded( false ) {
		load( "", "" );
	}

	Shader::~Shader() {
		//glDetachShader( program )
		glDeleteProgram( program );
	}

	Shader& Shader::load( std::string vertexSrc, std::string fragmentSrc ) {
		this->vertexSrc = vertexSrc.empty() ? getDefaultVertex() : vertexSrc;
		this->fragmentSrc = fragmentSrc.empty() ? getDefaultFragment() : fragmentSrc;
		return *this;
	}

	void Shader::compile() {

		if ( compilation_succeded == true )
			return;

		compilation_succeded = true;
		
		if ( vertexSrc.empty() || fragmentSrc.empty() ) {
			Log::error( "Vertex or fragment sources are empty. Cannot compile shader." );
			return;
		};
		
		// Vertex
		const char* vSrc = vertexSrc.c_str();
		GLuint vs = glCreateShader( GL_VERTEX_SHADER );
		glShaderSource( vs, 1, &vSrc, NULL );
		glCompileShader( vs );
		handleShaderErrors( vs, "VERTEX" );

		// Fragment
		const char* fSrc = fragmentSrc.c_str();
		GLuint fs = glCreateShader( GL_FRAGMENT_SHADER );
		glShaderSource( fs, 1, &fSrc, NULL );
		glCompileShader( fs );
		handleShaderErrors( fs, "FRAGMENT" );

		// Program
		program = glCreateProgram();
		glAttachShader( program, vs );
		glAttachShader( program, fs );
		glLinkProgram( program );
		handleProgramErrors( program );

		// Cleanup
		glDeleteShader( vs );
		glDeleteShader( fs );
	}

	GLuint Shader::getProgram() const {
		return this->program;
	}

	void Shader::handleShaderErrors( GLuint shader, std::string label ) {
		GLint succeded;
		glGetShaderiv( shader, GL_COMPILE_STATUS, &succeded );
		if ( ! succeded ) {
			GLchar outBuff[ 2048 ];
			glGetShaderInfoLog( shader, 2048, NULL, outBuff );
			Log::error( "(" + label + ") Shader compile error:" );
			Log::error( outBuff );
			compilation_succeded = false;
		}
	}

	void Shader::handleProgramErrors( GLuint program ) {
		GLint succeded;
		glGetProgramiv( program, GL_LINK_STATUS, &succeded );
		if ( ! succeded ) {
			GLchar outBuff[ 2048 ];
			glGetProgramInfoLog( program, 2048, NULL, outBuff );
			Log::error( "Program compile error:" );
			Log::error( outBuff );
			compilation_succeded = false;
		}
	}

	Shader& Shader::use() {
		compile();
		if ( compilation_succeded == true ) {
			glUseProgram( this->program );
		} else {
			Log::error( "Cannot use current shader. Compilation was unsuccessfull." );
		}
		return *this;
	}

	std::string Shader::getDefaultVertex() {
		return
			"#version 120\n"
			"attribute vec4 a_position;\n"
			"void main() {\n"
			"	gl_Position = vec4( a_position.x, a_position.y, a_position.z, 1.0 );\n"
			"}";
	}

	std::string Shader::getDefaultFragment() {
		return
			"#version 120\n"
			"precision mediump float;\n"
			"void main() {\n"
			"	gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);\n"
			"}";
		
	}

	GLint Shader::getAttr( const GLchar* name ) const {
		if ( !attributes.count( name ) ) {
			GLint location = glGetAttribLocation( this->program, name );
			if ( location > -1 ) {
				attributes[ name ] = location;
				return location;
			} else {
				Log::warn( "Attribute name:" + to_string( name ) + " doesn't exist in current shader." );
				return 0;
			}
		} else {
			return attributes.at( name );
		}
	}

	void Shader::setMatrix4( const GLchar* name, const glm::mat4& value ) const {
		glUniformMatrix4fv( glGetUniformLocation( program, name ), 1, GL_FALSE, glm::value_ptr( value ) );
	}

	void Shader::setVector3f( const GLchar* name, const glm::vec3 &value ) const {
		glUniform3f( glGetUniformLocation( program, name ), value.x, value.y, value.z );
	}

	void Shader::setInteger( const GLchar* name, const GLuint &value ) const {
		glUniform1i( glGetUniformLocation( program, name ), value );
	}

}