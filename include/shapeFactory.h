#ifndef SHAPE_H
#define SHAPE_H

#include "utilities.h"
#include <memory>
#include <string>
#include <glm/glm.hpp>          // The main GLM header
#include <glm/gtc/type_ptr.hpp>  // For glm::value_ptr
#include <vector>

//TODO: Update to use indexing 

class Shape {
public:
    virtual void init(std::string, std::string) = 0;
    virtual void update(const glm::vec2&, float) = 0; 
    virtual void render() = 0;
    virtual void useShaderProg() = 0;
    virtual void draw() = 0;
    virtual void generateCircleVertices() { };
    
    virtual void setWidthHeight(int, int) { };
    virtual void setRadius(int) { };
    virtual std::vector<std::string> getBinding() { };
    
    virtual ~Shape() = default;
};

class ShapeFactory {
public:
    std::shared_ptr<Shape> createShape(const std::string& shapeType);
};

class Circle : public Shape {
private:
    static const int vertexCount = 30; // 36 vertices for a smoother circle
    float vertices[vertexCount * 3] = {}; // 3 components (x, y, z) per vertex
    int radius;
    unsigned int VBO;
    unsigned int VAO;
    unsigned int shaderProgram;
    glm::mat4 transformationMatrix;

public:
    void init(std::string, std::string) override;
    void update(const glm::vec2&, float) override;
    void render() override;
    void useShaderProg() override;
    void draw() override;

    void setRadius(int r) override {
        radius = r;
    }

    void generateCircleVertices() override {
        for (int i = 0; i < vertexCount; ++i) {
            float angle = 2.0f * M_PI * float(i) / float(vertexCount);

            vertices[i * 3] = radius * cos(angle);
            vertices[i * 3 + 1] = radius * sin(angle);      // y-coordinate
            vertices[i * 3 + 2] = 0.0f;                     // z-coordinate
        }
    }
};

#endif // SHAPE_H
