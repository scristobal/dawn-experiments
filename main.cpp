#include <GLFW/glfw3.h>
#include <webgpu/webgpu.h>

#include <iostream>

WGPUAdapter requestAdapter(WGPUInstance instance, WGPURequestAdapterOptions const* options) {
    struct UserData {
        WGPUAdapter adapter = nullptr;
        bool requestEnded = false;
    };
    UserData userData;

    auto onAdapterRequestEnded = [](WGPURequestAdapterStatus status, WGPUAdapter adapter, char const* message, void* pUserData) {
        UserData& userData = *reinterpret_cast<UserData*>(pUserData);

        if (status == WGPURequestAdapterStatus_Success) {
            userData.adapter = adapter;
        } else {
            std::cout << "Could not find a suitable adapter: " << message << std::endl;
        }

        userData.requestEnded = true;
    };

    wgpuInstanceRequestAdapter(instance, options, onAdapterRequestEnded, &userData);

    assert(userData.requestEnded);

    return userData.adapter;
}

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

    WGPUInstanceDescriptor desc = {};
    desc.nextInChain = nullptr;

    WGPUInstance instance = wgpuCreateInstance(&desc);

    if (!instance) {
        std::cerr << "Could not create WebGPU instance!" << std::endl;
        return 1;
    }

    std::cout << "Requesting adapter..." << std::endl;

    WGPURequestAdapterOptions adapterOpts = {};
    WGPUAdapter adapter = requestAdapter(instance, &adapterOpts);

    std::cout << "Got adapter: " << adapter << std::endl;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();  // waits for events
    }

    wgpuAdapterRelease(adapter);

    glfwDestroyWindow(window);

    glfwTerminate();

    wgpuInstanceRelease(instance);

    std::cout << "Hello, world!" << std::endl;
    return 0;
}