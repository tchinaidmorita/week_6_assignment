#pragma once
#include "../wolf/wolf.h"
#include <vector>

struct Vertex
{
    GLfloat x, y, z;
    GLubyte r, g, b, a;
};

class Plane
{
public:
    Plane(int subdivisions = 5); // 5 subdivisions = 32x32 quads (2048 triangles)
    ~Plane();

    void init();
    void update(float dt);
    void render(const glm::mat4& view, const glm::mat4& proj);

    void setPosition(const glm::vec3& pos);
    void setRotation(const glm::vec3& rot);
    void setScale(const glm::vec3& scale);
    void setColor(const glm::vec4& col);

private:
    GLuint m_program = 0;
    GLuint m_vbo = 0;
    GLuint m_vao = 0;
    GLsizei m_vertexCount = 0;
    int m_subdivisions = 1;
    float m_totalTime = 0.0f;

    glm::vec3 m_position = glm::vec3(0.0f);
    glm::vec3 m_rotation = glm::vec3(0.0f);
    glm::vec3 m_scale    = glm::vec3(1.0f);
    glm::vec4 m_color    = glm::vec4(1.0f);
};