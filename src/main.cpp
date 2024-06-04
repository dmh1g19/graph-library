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

int main()
{
    GLFWwindow* window = initWindow(WIDTH, HEIGHT);
    initWorld(); // create the universal box2d world object 

    Graph G = Graph(true);
    for () {

    }
    G.addNode(1);
    G.addNode(2);
    G.addNode(3);
    G.addNode(4);
    G.addNode(5);
    G.setEdge(1, 2);
    G.setEdge(1, 3);
    G.setEdge(2, 1);

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

        addCircle(x, y, RADIUS, true);
        angle += angleIncrement;
    }

    // The following loop prints out each node in the graph and what nodes they're connected to
    //for (const auto pair : G.get_graph()) {
    //    std::cout << pair.first << " -> ";
    //    for (int i=0;i<pair.second->getEdges().size();i++) {
    //        std::cout << pair.second->getEdges()[i] << ", ";
    //    }
    //    std::cout << " " << std::endl;
    //}

    //G.setName(1, "Root");
    //G.printGraphData();
    //G.printAllNodeEdges();

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
