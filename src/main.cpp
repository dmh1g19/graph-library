#include "window.h"
#include "userInput.h"
#include "rendering.h"
#include "physics.h"
#include "graph.h"

double lastFrameTime = glfwGetTime();
const int RADIUS = 4; 
const int SPACING = 50;

int main()
{
    GLFWwindow* window = initWindow(WIDTH, HEIGHT);
    initWorld(); // create the universal box2d world object 

    createSimpleGraph(17);

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
