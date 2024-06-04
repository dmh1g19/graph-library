#include "shapeFactory.h"
#include "rendering.h"
#include <iostream>

unsigned int globalShaderProgEdge;

void Edge::init(std::string vertexShaderPath, std::string fragmentShaderPath) {
    initBuffers(VBO, VAO, vertices, sizeof(vertices));

    if (!globalShaderProgEdge) {
        std::cout << "Global edge shader initialized" << std::endl;
        globalShaderProgEdge = initShaders(vertexShaderPath, fragmentShaderPath);
    } else {
        std::cout << "Using global edge shader program" << std::endl;
    }
}

void Edge::update(const glm::vec2& position, float rotation) {
    transformationMatrix = glm::mat4(1.0f);
    transformationMatrix = glm::translate(transformationMatrix, glm::vec3(screenCoordsToOpenGL(position), 0.0f));
    transformationMatrix = glm::rotate(transformationMatrix, rotation, glm::vec3(0.0, 0.0, 1.0));
}

void Edge::render() {
    unsigned int transformLoc = glGetUniformLocation(globalShaderProgEdge, "transform");

    if (transformLoc == -1) {
        std::cerr << "Could not find uniform location for 'transform'" << std::endl;
    } else {
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformationMatrix));
    }
}

void Edge::useShaderProg() {
    useSpecificShader(globalShaderProgEdge);
}

void Edge::draw() {
    drawShape(globalShaderProgEdge, VAO, 0, 4, true); // Draw the edge as a triangle fan to form a rectangle
}

