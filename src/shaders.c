#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utils.h"

const char *read_shader_file(char *fname) {
    char filename[strlen("/shaders/") + strlen(fname)];
    sprintf(filename, "%s%s", "/shaders/", fname);
    return read_file(filename);
}

unsigned int create_shader_program() {
    printf("Compiling shaders...\n");
    printf("Compiling vertex shader...\n");
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char *vertexShaderSource = read_shader_file("vertex.glsl");
    if (vertexShaderSource == NULL) {
        return 0;
    }
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("Error: ShaderError: Vertex shader compilation failed.\n%s\n", infoLog);
    }

    printf("Compiling fragment shader...\n");
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragmentShaderSource = read_shader_file("fragment.glsl");
    if (fragmentShaderSource == NULL) {
        return 0;
    }
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("Error: ShaderError: Fragment shader compilation failed.\n%s\n", infoLog);
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    
    printf("Linking shaders to shader program with ID: %i\n", shaderProgram);

    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("Error: ShaderError: Shader linking failed.\n%s\n", infoLog);
    }

    // after linking the shaders, we no longer need them
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    free((char *)vertexShaderSource);
    free((char *)fragmentShaderSource);

    return shaderProgram;
}

void use_shader_program(unsigned int ID) {
    glUseProgram(ID);
}