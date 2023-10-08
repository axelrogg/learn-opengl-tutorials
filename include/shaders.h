#ifndef SHADERS_H
#define SHADERS_H

/**
 *  @brief Reads the contents of a shader inside `shaders/` directory, and
 *         returns a buffer with its content.
 *  @param fname Name of the shader file.
*/
const char *read_shader_file(char *fname);

/**
 *  @brief Compiles and links all shader sources to a shader program and returns
 *         its ID.
*/
unsigned int create_shader_program();

/**
 *  @brief Wraps around `glUseProgram`.
*/
void use_shader_program(unsigned int ID);

#endif