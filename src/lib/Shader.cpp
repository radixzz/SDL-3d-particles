#include "Shader.h"
#include "Resources.h"
#include "Log.h"

namespace sax {

	Shader::Shader(): program( 0 ) {
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
			"attribute vec4 position;"
			"void main() {"
			"	gl_Position = vec4( position.x, position.y, position.z, 1.0 );"
			"}";
	}

	std::string Shader::getDefaultFragment() {
		return
			"precision mediump float;"
			"void main() {"
			"	gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);"
			"}";
	}

}