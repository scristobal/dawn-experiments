#include <GLFW/glfw3.h>
#include <webgpu/webgpu.h>

#include <iostream>

int main(int, char**) {
    if (!glfwInit()) {
        std::cerr << "Could not initialize GLFW!" << std::endl;
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Learn WebGPU", NULL, NULL);

    if (!window) {
        std::cerr << "Could not open window!" << std::endl;
        glfwTerminate();
        return 1;
    }

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();  // waits for events
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    std::cout << "Hello, world!" << std::endl;
    return 0;
}