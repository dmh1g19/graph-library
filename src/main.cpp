#include "window.h"
#include "userInput.h"
#include "rendering.h"
#include "physics.h"
#include "utilities.h"
#include "shapeFactory.h"
#include "graph.h"
#include <vector>
#include <string>
#include <cmath> 

double lastFrameTime = glfwGetTime();
const int RADIUS = 4; 
const int SPACING = 50;

std::unordered_map<int, b2Body*> nodeBodyMap; 

int main()
{
    GLFWwindow* window = initWindow(WIDTH, HEIGHT);
    initWorld(); // create the universal box2d world object 

    Graph G = Graph(true);
    int totalNodes = 15;
    for (int i=0;i<totalNodes;i++) {
      G.addNode(i);
    }
    G.setEdge(1, 2);
    G.setEdge(2, 3);
    G.setEdge(3, 4);
    G.setEdge(4, 5);
    G.setEdge(6, 7);
    G.setEdge(8, 9);
    G.setEdge(10, 11);
    G.setEdge(12, 13);
    G.setEdge(13, 14);
    G.setEdge(14, 15);

    // Generate circles for each node
    const auto& graph = G.get_graph();
    int numNodes = graph.size();
    double angleIncrement = 2 * M_PI / numNodes;
    double angle = 0;

    for (const auto& pair : graph) {
      int nodeId = pair.first;

      // Calculate position using polar coordinates
      double x = WIDTH / 2 + SPACING * cos(angle);
      double y = HEIGHT / 2 + SPACING * sin(angle);

      b2Body* body = addCircle(x, y, RADIUS, true);
      nodeBodyMap[nodeId] = body; 
      angle += angleIncrement;
    }

    // Add joints (edges) between nodes
    for (const auto& pair : graph) {
        int nodeId = pair.first;
        const auto& edges = pair.second->getEdges();

        for (int targetNodeId : edges) {
            if (nodeBodyMap.find(targetNodeId) != nodeBodyMap.end()) {
                //std::cout << "Edge formed between " << nodeId << " and " << targetNodeId << std::endl;
                addDistanceJoint(nodeBodyMap[nodeId], nodeBodyMap[targetNodeId]);
                addEdge(nodeBodyMap[nodeId], nodeBodyMap[targetNodeId]);
            }
        }
    }

    while(!glfwWindowShouldClose(window))
    {
        double currentFrameTime = glfwGetTime();
        double deltaTime = currentFrameTime - lastFrameTime;

        if (deltaTime >= targetFrameTime)
        {
            stepPhysics();
            processInput(window);
            renderScene();
            glfwSwapBuffers(window);
            glfwPollEvents();

            lastFrameTime = currentFrameTime;
        }
    }

    glfwTerminate();
    return 0;
}
