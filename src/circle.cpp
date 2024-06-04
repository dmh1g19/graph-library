#include "shapeFactory.h"
#include "rendering.h"
#include "window.h"
#include "physics.h"
#include "utilities.h"
#include <iostream>

unsigned int globalShaderProg;

void Circle::init(std::string vertexShaderPath, std::string fragmentShaderPath) {
    initBuffers(VBO, VAO, vertices, sizeof(vertices));

    if(!globalShaderProg) {
        std::cout << "Gobal sphere shader initialized" << std::endl;
        globalShaderProg = initShaders(vertexShaderPath, fragmentShaderPath);
    }
    else {
        std::cout << "Using gobal sphere shader program" << std::endl;
    }
}

void Circle::update(const glm::vec2& position, float rotation) {
    //std::cout << "Updating position: " + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(rotation) << std::endl;
    transformationMatrix = glm::mat4(1.0f);
    transformationMatrix = glm::translate(transformationMatrix, glm::vec3(screenCoordsToOpenGL(position), 0.0f));
    transformationMatrix = glm::scale(transformationMatrix, glm::vec3(shapeSizeToOpenGLWidth(radius), shapeSizeToOpenGLHeight(radius), 1.0f));
    transformationMatrix = glm::rotate(transformationMatrix, rotation, glm::vec3(0.0, 0.0, 1.0));
}

void Circle::render() {
    unsigned int transformLoc = glGetUniformLocation(globalShaderProg, "transform");

    if (transformLoc == -1) {
        std::cerr << "Could not find uniform location for 'transform'" << std::endl;
    }
    else {
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformationMatrix));
    }
}

void Circle::useShaderProg() {
    useSpecificShader(globalShaderProg);
}

void Circle::draw() {
    int minVerts = 0;
    int maxVerts = 30*3;
    drawShape(globalShaderProg, VAO, minVerts, maxVerts, true);
}