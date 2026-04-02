#pragma once

struct GLFWwindow;
class Camera;

class Input {
public:
    explicit Input(GLFWwindow* window, Camera& camera);
    ~Input();

    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;

    void ProcessKeyboard(float deltaTime);
    void SetupCallbacks();
    void ProcessMouseMovement(double xposIn, double yposIn);
    void ProcessMouseScroll(double xoffset, double yoffset);

private:
    GLFWwindow* m_window;
    Camera& m_camera;
    float lastX = 0.0f, lastY = 0.0f;
    bool firstMouse = true;

    static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
};