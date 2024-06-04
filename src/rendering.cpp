#include "rendering.h"
#include <iostream>
#include <fstream>
#include <sstream>

/* 1 - Generating and Binding a VAO, 
   2 - Generating and Binding a VBO,
   3 - Setting Vertex Data in VBO, 
   4 - Configuring Vertex Attributes,
   5 - Draw the shape.
*/

std::string readShaderFromFile(std::string& filePath) {
    std::string shaderCode;
    std::ifstream shaderFile;

    // Ensure ifstream objects can throw exceptions
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        shaderFile.open(filePath);

        // Read file's buffer contents into streams
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderCode = shaderStream.str();
    } catch (std::ifstream::failure& e) {
        std::cerr << "Error: Failed to read shader file: " << e.what() << std::endl;
    }

    return shaderCode;
}

void initBuffers(unsigned int& VBO, unsigned int& VAO, float vertices[], size_t verticesSize) {
    // Generate and bind the Vertex Array Object first
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind the Vertex Buffer Object
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Allocate memory and initialize data for VBO
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind the VAO to prevent accidental modification (not strictly necessary but good practice)
    glBindVertexArray(0);

    std::cout << "1 - Initialized VAO and VBO" << std::endl;
}

unsigned int initShaders(std::string& path1, std::string& path2) {
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Attach the shader source code to the shader object and compile the shader
    std::string vertexShaderCode = readShaderFromFile(path1);
    const char* vertexShaderSource = vertexShaderCode.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, "VERTEX");
    std::cout << "2 - Initialized vertex shader" << std::endl;

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string fragmentShaderCode = readShaderFromFile(path2);
    const char* fragmentShaderSource = fragmentShaderCode.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");
    std::cout << "3 - Initialized fragment shader" << std::endl;
    
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();    

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkCompileErrors(shaderProgram, "PROGRAM");
    std::cout << "4 - Linked shaders" << std::endl;

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);  

    return shaderProgram;
}

void useSpecificShader(unsigned int shaderProgram) {
    //std::cout << "Using shader: " << std::to_string(shaderProgram) << std::endl;
    glUseProgram(shaderProgram);
}

void drawShape(unsigned int shaderProgram, unsigned int VAO, int minVertices, int maxVertices, bool isFan) {
    //std::cout << "Shader program ID: " + std::to_string(shaderProgram) << std::endl;
    glBindVertexArray(VAO);
    if(isFan) {
        glDrawArrays(GL_TRIANGLE_FAN, minVertices, maxVertices);
    }
    else {
        glDrawArrays(GL_TRIANGLES, minVertices, maxVertices);
    }
    glBindVertexArray(0);

    // Check for OpenGL errors after drawing
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error after drawing shape: " << getGLErrorString(err) << " (Error Code: " << err << ")" << std::endl;
    }

    //std::cout << "6 - Drew shape" << std::endl;
}

void checkCompileErrors(unsigned int shader, std::string type) {
    int success;
    char infoLog[1024];

    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n" << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n" << std::endl;
        }
    }
};

const char* getGLErrorString(GLenum err) {
    switch (err) {
        case GL_INVALID_ENUM:                  return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:                 return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:             return "GL_INVALID_OPERATION";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
        case GL_OUT_OF_MEMORY:                 return "GL_OUT_OF_MEMORY";
        case GL_STACK_UNDERFLOW:               return "GL_STACK_UNDERFLOW";
        case GL_STACK_OVERFLOW:                return "GL_STACK_OVERFLOW";
        default:                               return "Unknown Error";
    }
}
