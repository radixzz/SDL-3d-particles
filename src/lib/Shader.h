#ifndef SAX_SHADER_H
#define SAX_SHADER_H

#include <string.h>
#include <iostream>
#include <map>

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Utils.h"

namespace sax {
	class Shader {
		public:
			Shader();
			~Shader();
			Shader &use();
			Shader &load( std::string vertexSrc, std::string fragmentSrc );
			GLint getAttr( const GLchar* name ) const;
			void setMatrix4( const GLchar* name, const glm::mat4 &value ) const;
			void setVector3f( const GLchar* name, const glm::vec3 &value ) const;
			void setInteger( const GLchar* name, const GLuint &value ) const;
		private:
			void compile();
			void handleShaderErrors( GLuint shader, std::string labels );
			void handleProgramErrors( GLuint program );
			std::string getDefaultFragment();
			std::string getDefaultVertex();
			GLuint program;
			bool compilation_succeded;
			std::string vertexSrc;
			std::string fragmentSrc;
			mutable std::map< std::string, GLint > attributes;
	};
}

#endif
