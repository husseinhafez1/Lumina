#pragma once

#include <unordered_map>

struct GLFWwindow;
class Camera;
class Window;

class Input {
public:
    explicit Input(Window& window, Camera& camera);
    ~Input();

    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;

    void ProcessKeyboard(float deltaTime);
    void SetupCallbacks();
    void ProcessMouseMovement(double xposIn, double yposIn);
    void ProcessMouseScroll(double xoffset, double yoffset);

    bool isKeyJustPressed(int key);
private:
    Window& m_window;
    Camera& m_camera;
    std::unordered_map<int, bool> m_keyStates;
    float lastX = 400.0f, lastY = 300.0f;
    bool firstMouse = true;

    static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
};