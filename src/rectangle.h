#include "../include/glad/glad.h"
#include "../include/glm/glm.hpp"

class Rectangle {
public:
    // Constructor
    Rectangle(glm::vec2 position, glm::vec2 size, glm::vec3 color)
        : m_Position(position), m_Size(size), m_Color(color)
    {
        // Generate vertex buffer object (VBO)
        glGenBuffers(1, &m_VBO);

        // Generate vertex array object (VAO)
        glGenVertexArrays(1, &m_VAO);

        // Bind VAO
        glBindVertexArray(m_VAO);

        // Bind VBO
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        // Set vertex data
        float vertices[] = {
            // Position      // Color
			m_Position.x, m_Position.y,  m_Color.r, m_Color.g, m_Color.b,
			m_Position.x, m_Position.y + m_Size.y,  m_Color.r, m_Color.g, m_Color.b,
			m_Position.x + m_Size.x, m_Position.y,  m_Color.r, m_Color.g, m_Color.b,
			m_Position.x + m_Size.x, m_Position.y + m_Size.y, m_Color.r, m_Color.g, m_Color.b
};
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Set vertex attributes
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));

        // Unbind VBO and VAO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    // Destructor
    ~Rectangle()
    {
        glDeleteBuffers(1, &m_VBO);
        glDeleteVertexArrays(1, &m_VAO);
    }

    // Render function
    void Render()
    {
        // Bind VAO
        glBindVertexArray(m_VAO);

        // Draw rectangle
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        // Unbind VAO
        glBindVertexArray(0);
    }

    // Move function
    void Move(glm::vec2 offset)
    {
        m_Position += offset;

        // Update vertex positions
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        float vertices[] = {
            // Position      // Color
            m_Position.x, m_Position.y,                              m_Color.r, m_Color.g, m_Color.b,
            m_Position.x, m_Position.y + m_Size.y,                   m_Color.r, m_Color.g, m_Color.b,
            m_Position.x + m_Size.x, m_Position.y,                   m_Color.r, m_Color.g, m_Color.b,
            m_Position.x + m_Size.x, m_Position.y + m_Size.y,        m_Color.r, m_Color.g, m_Color.b
        };
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

private:
    glm::vec2 m_Position;
    glm::vec2 m_Size;
    glm::vec3 m_Color;
    GLuint m_VBO;
    GLuint m_VAO;
};
