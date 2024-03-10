#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#define __DEBUG__

#ifdef __DEBUG__
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x)
#endif

// Prototypes
static inline void framebuffer_size_callback(GLFWwindow *window, int width,
                                             int height);

static inline void processInput(GLFWwindow *window);

static unsigned int CreateShader(std::string shaderSource, int type);

static unsigned int CreateShaderProgram(std::string &vertexShaderSource,
                                        std::string &fragmentShaderSource);

static inline void glfwError(std::string msg) {
    std::cout << msg << std::endl;
    glfwTerminate();
}

// Settings
static const unsigned int SCREEN_WIDTH = 800;
static const unsigned int SCREEN_HEIGHT = 600;

int main(void) {
    // Initialize and configure glfw
    if (!glfwInit()) {
        glfwError("Failed to initialize GLFW!");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __MAC__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Glfw window creation
    GLFWwindow *window = glfwCreateWindow(
        SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Linux Template", nullptr, nullptr);
    if (window == nullptr) {
        glfwError("Failed to create GLFW window");
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Glew: load all OpenGL function pointers
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "GLEW initialization failed: " << glewGetErrorString(err)
                  << std::endl;
        return -1;
    }

    LOG("Initialized OpenGL\nOpenGL Version: " << glGetString(GL_VERSION));

    LOG("Starting to generate lil triangle");
    // Build and compile shader program
    LOG("Creating a shader program");
    std::string vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec4 aColor;\n"
        "out vec4 ourColor;\n" // Changed to 'out' variable
        "void main()\n"
        "{\n"
        "   ourColor = aColor;\n" // Assign aColor to ourColor
        "   gl_Position = vec4(aPos.xyz, 1.0);\n"
        "}\0";

    std::string fragmentShaderSource =
        "#version 330 core\n"
        "in vec4 ourColor;\n"   // Use ourColor from the vertex shader
        "out vec4 FragColor;\n" // Changed to 'out' variable
        "void main()\n"
        "{\n"
        "   FragColor = ourColor;\n" // Removed 'f' suffix
        "}\n\0";

    unsigned int shaderProgram =
        CreateShaderProgram(vertexShaderSource, fragmentShaderSource);

    float vertices[] = {
        //    Position     |      Color
        0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, // top right
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.8f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        -0.5f, 0.5f,  0.0f, 0.0f, 0.0f, 1.0f, // top left
    };

    unsigned int indices[] = {
        0, 1, 3, // First triangle (top-left, bottom-left, bottom-right)
        1, 2, 3  // Second triangle (top-left, bottom-right, top-right)
    };

    LOG("Creating VBOs, VAOs and EBOs");
    unsigned int VBO, VAO, EBO;

    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO
    glGenBuffers(1, &VBO); // Assign a buffer to the buffer object id thingy

    glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind the buffer to target

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                 GL_STATIC_DRAW); // loads data into buffer

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          6 * sizeof(float), // Position
                          (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), // Color
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // EBO
    glGenBuffers(1, &EBO); // Assign a buffer to the buffer object id thingy

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    // Unbind buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    LOG("Finished generatin our lil triangle");

    LOG("Starting main loop");

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    LOG("GLFW was terminated successfully");

    return 0;
}

static inline void framebuffer_size_callback(GLFWwindow *window, int width,
                                             int height) {
    glViewport(0, 0, width, height);
}

static inline void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) ==
        GLFW_PRESS) // Press escape to exit program
        glfwSetWindowShouldClose(window, true);

    static bool lock = 0, wf_mode = 0;
    if (!glfwGetKey(window, GLFW_KEY_W)) {
        lock = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_W) && lock == 0) {
        glPolygonMode(GL_FRONT_AND_BACK,
                      (wf_mode = 1 - wf_mode) ? GL_LINE : GL_FILL);
        lock = 1;
    }
}

static unsigned int CreateShader(std::string shaderSource, int type) {
    unsigned int shader;
    shader = glCreateShader(type);

    const char *sourcePtr = shaderSource.c_str();
    glShaderSource(shader, 1, &sourcePtr, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    return shader;
}

static unsigned int CreateShaderProgram(std::string &vertexShaderSource,
                                        std::string &fragmentShaderSource) {
    unsigned int vertexShader;
    vertexShader = CreateShader(vertexShaderSource, GL_VERTEX_SHADER);

    unsigned int fragmentShader;
    fragmentShader = CreateShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];

    glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    glDeleteProgram(vertexShader);
    glDeleteProgram(fragmentShader);

    return shaderProgram;
}
