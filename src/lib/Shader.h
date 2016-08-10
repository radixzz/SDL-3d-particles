#ifndef SAX_SHADER_H
#define SAX_SHADER_H

#include <GL\glew.h>
#include <string.h>
#include <iostream>

namespace sax {
	class Shader {
		public:
			Shader();
			~Shader();
			Shader &use();
			Shader &load( std::string vertexSrc, std::string fragmentSrc );
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
	};
}

#endif
