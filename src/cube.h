#include "../include/glad/glad.h"
#include "../include/glm/glm.hpp"
#include "../include/glm/ext.hpp"
#include "shader.h"

class Cube
{
public:
    Cube(const glm::vec3& position, float size, const glm::vec3& color)
        : m_Position(position), m_Size(size), m_Color(color)
    {
        // Define the vertices of the cube
        glGenBuffers(1, &m_VBO);

        // Generate vertex array object (VAO)
        glGenVertexArrays(1, &m_VAO);

        // Bind VAO
        glBindVertexArray(m_VAO);

        // Bind VBO
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        float halfSize = size / 2.0f;
        float vertices[] = {
            // Front face
            -halfSize, -halfSize,  halfSize, m_Color.r, m_Color.g, m_Color.b,
             halfSize, -halfSize,  halfSize, m_Color.r, m_Color.g, m_Color.b,
             halfSize,  halfSize,  halfSize, m_Color.r, m_Color.g, m_Color.b,
            -halfSize,  halfSize,  halfSize, m_Color.r, m_Color.g, m_Color.b,
            // Back face
            -halfSize, -halfSize, -halfSize, m_Color.r, m_Color.g, m_Color.b,
            -halfSize,  halfSize, -halfSize, m_Color.r, m_Color.g, m_Color.b,
             halfSize,  halfSize, -halfSize, m_Color.r, m_Color.g, m_Color.b,
             halfSize, -halfSize, -halfSize, m_Color.r, m_Color.g, m_Color.b,
            // Top face
            -halfSize,  halfSize, -halfSize, m_Color.r, m_Color.g, m_Color.b,
            -halfSize,  halfSize,  halfSize, m_Color.r, m_Color.g, m_Color.b,
             halfSize,  halfSize,  halfSize, m_Color.r, m_Color.g, m_Color.b,
             halfSize,  halfSize, -halfSize, m_Color.r, m_Color.g, m_Color.b,
            // Bottom face
            -halfSize, -halfSize, -halfSize, m_Color.r, m_Color.g, m_Color.b,
             halfSize, -halfSize, -halfSize, m_Color.r, m_Color.g, m_Color.b,
             halfSize, -halfSize,  halfSize, m_Color.r, m_Color.g, m_Color.b,
            -halfSize, -halfSize,  halfSize, m_Color.r, m_Color.g, m_Color.b,
            // Right face
             halfSize, -halfSize, -halfSize, m_Color.r, m_Color.g, m_Color.b,
             halfSize,  halfSize, -halfSize, m_Color.r, m_Color.g, m_Color.b,
             halfSize,  halfSize,  halfSize, m_Color.r, m_Color.g, m_Color.b,
             halfSize, -halfSize,  halfSize, m_Color.r, m_Color.g, m_Color.b,
            // Left face
            -halfSize, -halfSize, -halfSize, m_Color.r, m_Color.g, m_Color.b,
            -halfSize, -halfSize,  halfSize, m_Color.r, m_Color.g, m_Color.b,
            -halfSize,  halfSize,  halfSize, m_Color.r, m_Color.g, m_Color.b,
            -halfSize,  halfSize, -halfSize, m_Color.r, m_Color.g, m_Color.b
        };
        // Set up the vertex buffer object and vertex array object
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	}
    ~Cube()
    {
        glDeleteBuffers(1, &m_VBO);
        glDeleteVertexArrays(1, &m_VAO);
    }
    void Render(Shader* shader, float dt)
    {
        // Bind VAO
        glBindVertexArray(m_VAO);


		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, m_Position);
		model = glm::rotate(model, dt * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		shader->setMat4f("model", model);

        // Draw rectangle
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 36);

        // Unbind VAO
        glBindVertexArray(0);
    }

private:
    glm::vec3 m_Position;
    float m_Size;
    glm::vec3 m_Color;
    GLuint m_VBO;
    GLuint m_VAO;
};

