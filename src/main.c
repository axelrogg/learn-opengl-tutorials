#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

#ifndef TEXT_COLOR_HEX
    #define TEXT_COLOR_HEX "#eae9fc"
#endif
#ifndef BACKGROUND_COLOR_HEX
    #define BACKGROUND_COLOR_HEX "#010104"
#endif
#ifndef PRIMARY_COLOR_HEX
    #define PRIMARY_COLOR_HEX "#3d1363"
#endif
#ifndef SECONDARY_COLOR_HEX
    #define SECONDARY_COLOR_HEX "#1d1d2a"
#endif
#ifndef ACCENT_COLOR_HEX
    #define ACCENT_COLOR_HEX "#7373a0"
#endif


/**
 *  @brief Represents a color in the RGB color space.
 */
typedef struct {
    float R;
    float G;
    float B;
} ColorRGB;

/**
 *  @brief Converts a hexadecimal color string to a ColorRGB structure.
 *  
 *  This function takes a hexadecimal color string and converts it into its
 *  corresponding RGB components stored in a ColorRGB structure.
 *
 *  @param hex   The input hexadecimal color string (e.g., "#FFAABB").
 *  @param color Pointer to a ColorRGB structure where the RGB components will
 *               be stored. The structure should be allocated by the caller.
*/
void colorHexStringToColorRGB(char *hex, ColorRGB *color);

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
void initGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // MacOS only
}

/**
 * @brief Initialize GLAD.
 * 
 * Loads the address of the OpenGL function pointers.
*/
int initGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Error: Failed to initialize GLAD");
        return -1;
    }
    return 0;
}

int main() {
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

void colorHexStringToColorRGB(char *hex, ColorRGB *color) {
    unsigned long hexValue = strtoul(hex + 1, NULL, 16);
    color->R = ((hexValue >> 16) & 0xFF) / 255.0;
    color->G = ((hexValue >> 8)  & 0xFF) / 255.0;
    color->B = ((hexValue)       & 0xFF) / 255.0;
}