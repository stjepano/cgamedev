#ifndef GLTOOLS_H_
#define GLTOOLS_H_

//
// OpenGL tools
//

#include <GL/glew.h>
#include "defines.h"

/// Compile shader
error_t GLT_CompileShader(GLenum shader_type, const char* source, GLuint* out);

/// Link shaders into new GLSL program
error_t GLT_CreateProgram(const GLuint* shaders, size_t shaders_sz, bool delete_shaders, GLuint* out);


#endif // GLTOOLS_H_