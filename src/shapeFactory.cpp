#include "shapeFactory.h"
#include <memory>
#include <iostream>

std::shared_ptr<Shape> ShapeFactory::createShape(const std::string& shapeType) {
    if (shapeType == "Circle") {
        return std::make_unique<Circle>();
    }
    else if (shapeType == "Edge") {
        return std::make_unique<Edge>();
    }
    else {
        std::cout << "Unknown shape type" << std::endl;
        return nullptr; // Return nullptr to indicate an unknown shape type.
    }
}
