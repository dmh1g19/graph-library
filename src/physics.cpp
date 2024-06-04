#include "physics.h"
#include "utilities.h"
#include "shapeFactory.h"
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <cmath>

b2World* world;
ShapeFactory factory;
std::unordered_map<b2Body*, std::shared_ptr<Shape>> bodyShapeMap;
std::vector<std::tuple<b2Body*, b2Body*, std::vector<b2Body*>>> edgeCircles; // Store the nodes and the circles that form the edges

void stepPhysics() {
    world->Step(simulationFrameRate, velocityIteration, positionIteration);

    // Update edge circles' positions based on the nodes they connect
    for (const auto& edge : edgeCircles) {
        b2Body* bodyA = std::get<0>(edge);
        b2Body* bodyB = std::get<1>(edge);
        const auto& circles = std::get<2>(edge);

        b2Vec2 posA = bodyA->GetWorldCenter();
        b2Vec2 posB = bodyB->GetWorldCenter();
        b2Vec2 direction = posB - posA;
        float distance = direction.Length();
        direction.Normalize();

        float spacing = distance / (circles.size() + 1);

        for (size_t i = 0; i < circles.size(); ++i) {
            b2Vec2 pos = posA + (i + 1) * spacing * direction;
            circles[i]->SetTransform(pos, 0);
        }
    }
}

void initWorld() {
    world = new b2World(b2Vec2(0.0f, gravity));
}

b2Body* addCircle(int x, int y, int radius, bool dyn) {
    std::cout << "\nMade circle at " + std::to_string(x) + ", " + std::to_string(y) << std::endl;

    b2BodyDef bodydef;
    bodydef.position.Set(pixels2Meters(x), pixels2Meters(y));
    if (dyn) {
        bodydef.type = b2_dynamicBody;
    }
    b2Body* body = world->CreateBody(&bodydef);

    int spacing = 3;
    b2CircleShape shape;
    shape.m_radius = pixels2Meters(radius*radius+spacing);

    b2FixtureDef fixturedef;
    fixturedef.shape = &shape;
    fixturedef.density = dynamicBodyDensity;
    body->CreateFixture(&fixturedef);

    std::shared_ptr<Shape> circle = factory.createShape("Circle");
    circle->setRadius(radius);
    circle->generateCircleVertices();
    addToMap(circle, body, "shaders/vertex_shader_circle.glsl", "shaders/fragment_shader_circle.glsl");

    return body;
}

void addDistanceJoint(b2Body* bodyA, b2Body* bodyB) {
    b2DistanceJointDef jointDef;
    jointDef.bodyA = bodyA;
    jointDef.bodyB = bodyB;
    jointDef.localAnchorA.Set(0, 0);
    jointDef.localAnchorB.Set(0, 0);
    jointDef.collideConnected = false;

    b2Vec2 posA = bodyA->GetWorldCenter();
    b2Vec2 posB = bodyB->GetWorldCenter();
    jointDef.length = (posB - posA).Length();

    world->CreateJoint(&jointDef);
}

void addEdge(b2Body* bodyA, b2Body* bodyB) {
    const b2Vec2& posA = bodyA->GetWorldCenter();
    const b2Vec2& posB = bodyB->GetWorldCenter();
    std::cout << "\nMade Edge at " << meters2Pixels(posA.x) << ", " << meters2Pixels(posA.y)
              << " and " << meters2Pixels(posB.x) << ", " << meters2Pixels(posB.y) << std::endl;

    // Calculate the direction vector and distance between the two points
    b2Vec2 direction = posB - posA;
    float distance = direction.Length();
    direction.Normalize();

    int numCircles = static_cast<int>(distance / pixels2Meters(2)); 
    float spacing = distance / numCircles;

    std::vector<b2Body*> circles;
    for (int i = 1; i < numCircles; ++i) {
        b2Vec2 pos = posA + i * spacing * direction;
        int x = meters2Pixels(pos.x);
        int y = meters2Pixels(pos.y);
        b2Body* circleBody = addCircle(x, y, 1, false); 
        circles.push_back(circleBody);
    }

    edgeCircles.emplace_back(bodyA, bodyB, circles);
}

// Associate the shape with the body in a map, this basically adds the object to the world
void addToMap(std::shared_ptr<Shape> object, b2Body* body, std::string vertexShader, std::string fragmentShader) {
    object->init(vertexShader, fragmentShader);
    bodyShapeMap[body] = object;
}

// Draw all the objects in the scene after associating the box2d objects with the opengl shapes
void renderScene() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (const auto& pair : bodyShapeMap) {
        b2Body* body = pair.first;
        std::shared_ptr<Shape> shape = pair.second;

        const b2Vec2& position = body->GetPosition();
        float angle = body->GetAngle();

        shape->useShaderProg();
        shape->update(glm::vec2(meters2Pixels(position.x), meters2Pixels(position.y)), angle / -1); // Have to invert the angle for opengl
        shape->render();
        shape->draw();
    }
}

