#pragma once

#include <iostream>
#include <stdexcept>
#include "Camera.h"

struct GLFWwindow;

class Window {
private:
    GLFWwindow* window;
public:
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete;

    Window(unsigned int width = 800, unsigned int height = 600);
    ~Window();

    GLFWwindow* GetHandle() const { return window; }

    bool isClosed() const;
};