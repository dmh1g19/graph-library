#ifndef PHYSICS_H
#define PHYSICS_H

/* the frame rate and physics is dependent on the window size */

#include "window.h"
#include "shapeFactory.h"
#include <box2d/box2d.h>
#include <memory>
#include <vector>
#include <string>

// Global pointer to the Box2D world
extern b2World* world;

const float simulationFrameRate = 1.0 / framesPerSecond;
const float dynamicBodyDensity = 1.0;

const int velocityIteration = 8;
const int positionIteration = 3;
const int gravity = 0;

void stepPhysics();
void renderScene();
void addToMap(std::shared_ptr<Shape>, b2Body*, std::string, std::string);

b2Body* addCircle(int, int, int, bool, int);
void addDistanceJoint(b2Body*, b2Body*);
void addEdge(b2Body* , b2Body* );
void initWorld();

std::vector<b2Vec2> parsePolygonCoordinates(const std::string&);
extern std::vector<std::shared_ptr<Edge>> edgeList;

#endif // PHYSICS_H
