#include "../include/glm/glm.hpp"
#include "../include/glm/ext.hpp"
#define SPEED 4
#define SENSITIVITY 4
#define ZOOM 4

enum class Camera_movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) :
        m_Position(position),
        m_WorldUp(up),
        m_Yaw(yaw),
        m_Pitch(pitch),
        m_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
        m_MovementSpeed(SPEED),
        m_MouseSensitivity(SENSITIVITY),
        m_Zoom(ZOOM)
    {
        updateCameraVectors();
    }

    glm::mat4 getViewMatrix()
    {
        return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    }

    void processKeyboard(Camera_movement direction, float deltaTime)
    {
        float velocity = m_MovementSpeed * deltaTime;
        if (direction == Camera_movement::FORWARD)
            m_Position += m_Front * velocity;
        if (direction == Camera_movement::BACKWARD)
            m_Position -= m_Front * velocity;
        if (direction == Camera_movement::LEFT)
            m_Position -= m_Right * velocity;
        if (direction == Camera_movement::RIGHT)
            m_Position += m_Right * velocity;
    }

    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
    {
        xoffset *= m_MouseSensitivity;
        yoffset *= m_MouseSensitivity;

        m_Yaw += xoffset;
        m_Pitch += yoffset;

        if (constrainPitch)
        {
            if (m_Pitch > 89.0f)
                m_Pitch = 89.0f;
            if (m_Pitch < -89.0f)
                m_Pitch = -89.0f;
        }

        updateCameraVectors();
    }

    void processMouseScroll(float yoffset)
    {
        if (m_Zoom >= 1.0f && m_Zoom <= 45.0f)
            m_Zoom -= yoffset;
        if (m_Zoom <= 1.0f)
            m_Zoom = 1.0f;
        if (m_Zoom >= 45.0f)
            m_Zoom = 45.0f;
    }

private:
    // Camera Attributes
    glm::vec3 m_Position;
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    glm::vec3 m_WorldUp;
    // Euler Angles
    float m_Yaw;
    float m_Pitch;
    // Camera options
    float m_MovementSpeed;
    float m_MouseSensitivity;
    float m_Zoom;

    void updateCameraVectors()
    {
        // Calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        front.y = sin(glm::radians(m_Pitch));
        front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_Front = glm::normalize(front);
        // Re-calculate the Right and Up vector
        m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));  
        m_Up = glm::normalize(glm::cross(m_Right, m_Front));
    }
};
