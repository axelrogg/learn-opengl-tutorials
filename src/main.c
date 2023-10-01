#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utils.h"

#ifndef SNAKE_VERSION
    #define SNAKE_VERSION "0.0.1"
#endif

#ifdef _WIN64
    #define OS_NAME "Windows 64-bit"
#elif _WIN32
    #define OS_NAME "Windows 32-bit"
#elif __linux__
    #define OS_NAME "Linux"
#elif __unix__
    #define OS_NAME "Unix"
#else
    #define OS_NAME "Unknown"
#endif


/**
 *  @brief GLFW function: Whenever the window size changed (by the OS or user
 *  resize) this callback function executes.
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

/**
 *  @brief Process all input: Query GLFW whether relevant keys are pressed/
 *  released, and react accordingly.
*/
void processInput(GLFWwindow *window);

/**
 * @brief Initialize GLFW
 * 
 * Tells GLFW that we use version 3.3, and the core-profile.
 * Telling GLFW we want to use the core-profile means we'll get access to a
 * smaller subset of OpenGL features without backwards-compatible features we
 * don't need.
*/
void initGLFW();

/**
 * @brief Initialize GLAD.
 * 
 * Loads the address of the OpenGL function pointers. It must be run after
 * a `GLFWwindow` window has been selected as current context (by calling
 * `glfwMakeContextCurrent`.)
*/
int initGLAD();

int main(void) {
    printf("Starting Snake v%s\n----------\n", SNAKE_VERSION);
    printf("Operating System: %s\n----------\n", OS_NAME);

    initGLFW();
    GLFWwindow* window = glfwCreateWindow(800, 600, "Snake", NULL, NULL);
    if (window == NULL) {
        printf("Error: Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (initGLAD() == -1) {
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    char *backgroundHex = BACKGROUND_COLOR_HEX;
    ColorRGB backgroundRGB;
    colorHexStringToColorRGB(backgroundHex, &backgroundRGB);
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(backgroundRGB.R, backgroundRGB.G, backgroundRGB.B, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void initGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // MacOS only
}

int initGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Error: Failed to initialize GLAD");
        return -1;
    }
    return 0;
}