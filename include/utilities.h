#ifndef UTILITIES_H
#define UTILITIES_H

#include "window.h"
#include <glm/glm.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include <vector>
#include <algorithm>

// Conversion constants between meters and pixels
const float M2P = 60.0f;
const float P2M = 1.0f / M2P;

glm::vec2 screenCoordsToOpenGL(const glm::vec2&);
glm::vec2 shapeSizeToOpenGL(float, float);

float shapeSizeToOpenGLWidth(float);
float shapeSizeToOpenGLHeight(float);
float pixels2Meters(float);
float meters2Pixels(float);

void printShaderProgramMatrix(glm::mat4 transformationMatrix);
std::vector<b2Vec2> parsePolygonCoordinates(const std::string&);

#endif // UTILITIES_H
