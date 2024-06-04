#include "userInput.h"
#include "shapeFactory.h"
#include "physics.h"
#include "utilities.h"
#include <iostream>
#include <thread>
#include <chrono>

bool mousePressed = false;

std::chrono::time_point<std::chrono::system_clock> lastMouseClickTime;  // Initialize a timestamp
const std::chrono::duration<float> cooldownDuration(0.2); //in seconds

double xpos;
double ypos;

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        delete world;
    }
    else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        auto currentTime = std::chrono::system_clock::now();
        
        if((currentTime - lastMouseClickTime >= cooldownDuration)) {
            glfwGetCursorPos(window, &xpos, &ypos);
            addCircle(xpos, ypos, 4, true, 3); 
            
            lastMouseClickTime = currentTime;
        }
    }
}
