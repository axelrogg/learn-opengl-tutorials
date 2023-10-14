#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

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

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void set_app_callbacks(GLFWwindow* window);

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

    set_app_callbacks(window);

    unsigned int shaderProgramID = create_shader_program();
    if(shaderProgramID == 0) {
        return -1;
    }

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("/home/axelrogg/projects/int/snake/textures/container.jpg", &width, &height, &nrChannels, 0); 
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("TextureError: Failed to load texture\n");
        return -1;
    }
    stbi_image_free(data);


    char *backgroundHex = BACKGROUND_COLOR_HEX;
    ColorRGB backgroundRGB;
    colorHexStringToColorRGB(backgroundHex, &backgroundRGB);
    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(backgroundRGB.R, backgroundRGB.G, backgroundRGB.B, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);



        // use our shader program
        use_shader_program(shaderProgramID);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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

void set_app_callbacks(GLFWwindow* window) {
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    // (void)printf("Cursor position: (%f, %f)\n", xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        (void)printf("Pressed right mouse button\n");
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        (void)printf("Pressed left mouse button\n");
    }
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