#include "gltools.h"

#define GLT_ERR_CODE 31

const char* GetOpenGLErrorDescription(GLenum gl_error);

#define CHECK_GL_ERROR() { GLenum err = glGetError(); if (err != GL_NO_ERROR) return Error(GLT_ERR_CODE, "OpenGL error: %s", GetOpenGLErrorDescription(err)); }

error_t GLT_CompileShader(GLenum shader_type, const char* source, GLuint* out)
{
    GLuint shader = glCreateShader(shader_type);
    CHECK_GL_ERROR();   
    glShaderSource(shader, 1, &source, NULL);
    CHECK_GL_ERROR();
    glCompileShader(shader);

    GLint success;
    GLchar infolog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infolog);
        return Error(GLT_ERR_CODE, "Failed to compile shader: %s", infolog);
    }
    (*out) = shader;
    return NoError();
}



error_t GLT_CreateProgram(const GLuint* shaders, size_t shaders_sz, bool delete_shaders, GLuint* out)
{
    GLuint program = glCreateProgram();
    CHECK_GL_ERROR();

    for (size_t i = 0; i < shaders_sz; i++)
    {
        glAttachShader(program, shaders[i]);
    }
    glLinkProgram(program);

    GLint success;
    GLchar infolog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infolog);
        return Error(GLT_ERR_CODE, "Failed to link shaders into program: %s", infolog);
    }

    if (delete_shaders)
    {
        for (size_t i = 0; i < shaders_sz; i++)
        {
            glDeleteShader(shaders[i]);
        }
    }

    (*out) = program;
    return NoError();
}


typedef struct glerr_description_s {
    GLenum gl_err_code;
    const char* description;
} glerr_description_t;

glerr_description_t glerr_description[] = {
    {GL_INVALID_ENUM, "An unacceptable value is specified for an enumerated argument."},
    {GL_INVALID_VALUE, "A numeric argument is out of range."},
    {GL_INVALID_OPERATION, "The specified operation is not allowed in the current state."},
    {GL_INVALID_FRAMEBUFFER_OPERATION, "The framebuffer object is not complete."},
    {GL_OUT_OF_MEMORY, "There is not enough memory left to execute the command."},
    {GL_STACK_UNDERFLOW, "An attempt has been made to perform an operation that would cause an internal stack to underflow."},
    {GL_STACK_OVERFLOW, "An attempt has been made to perform an operation that would cause an internal stack to overflow."}
};


#define GL_ERROR_SIZE 7
#define NOT_FOUND_GL_ERROR "Unknown Open GL error"

const char* GetOpenGLErrorDescription(GLenum gl_error)
{
    for (int i = 0; i < GL_ERROR_SIZE; i++)
    {
        if (glerr_description[i].gl_err_code == gl_error)
        {
            return glerr_description[i].description;
        }
    }
    return NOT_FOUND_GL_ERROR;
}