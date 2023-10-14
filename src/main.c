#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaders.h"
#include "utils.h"

#define SNAKE_VERSION "0.0.1"

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
void process_input(GLFWwindow *window);

/**
 * @brief Initialize GLFW
 * 
 * Tells GLFW that we use version 3.3, and the core-profile.
 * Telling GLFW we want to use the core-profile means we'll get access to a
 * smaller subset of OpenGL features without backwards-compatible features we
 * don't need.
*/
void init_GLFW();

/**
 * @brief Initialize GLAD.
 * 
 * Loads the address of the OpenGL function pointers. It must be run after
 * a `GLFWwindow` window has been selected as current context (by calling
 * `glfwMakeContextCurrent`.)
*/
int init_GLAD();

int main(void) {
    printf("Starting Snake v%s\n----------\n", SNAKE_VERSION);
    printf("Operating System: %s\n----------\n", OS_NAME);

    init_GLFW();
    GLFWwindow* window = glfwCreateWindow(800, 600, "Snake", NULL, NULL);
    if (window == NULL) {
        printf("Error: Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (init_GLAD() == -1) {
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    unsigned int shaderProgramID = create_shader_program();
    if(shaderProgramID == 0) {
        return -1;
    }

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);  // GL_ARRAY_BUFFER is the buffer type of a vertex buffer object
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    char *backgroundHex = BACKGROUND_COLOR_HEX;
    ColorRGB backgroundRGB;
    colorHexStringToColorRGB(backgroundHex, &backgroundRGB);
    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(backgroundRGB.R, backgroundRGB.G, backgroundRGB.B, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        float timeValue = glfwGetTime();
        float greenValue = fabs(sin((timeValue)));
        int vertexColorLocation = glGetUniformLocation(shaderProgramID, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // use our shader program
        use_shader_program(shaderProgramID);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void process_input(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void init_GLFW() {
    printf("Starting GLFW v3.38\n----------\n");

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // MacOS only
}

int init_GLAD() {
    printf("Starting Glad v4.6\n----------\n");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Error: Failed to initialize GLAD");
        return -1;
    }
    return 0;
}