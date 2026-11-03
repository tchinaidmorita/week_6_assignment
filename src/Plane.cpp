#include "Plane.h"

Plane::Plane(int subdivisions)
    : m_subdivisions(subdivisions)
{
    if (m_subdivisions < 1) m_subdivisions = 1;
}

Plane::~Plane()
{
    if (m_vbo != 0) glDeleteBuffers(1, &m_vbo);
    if (m_vao != 0) glDeleteVertexArrays(1, &m_vao);
}

void Plane::setPosition(const glm::vec3& pos) { m_position = pos; }
void Plane::setRotation(const glm::vec3& rot) { m_rotation = rot; }
void Plane::setScale(const glm::vec3& scale)   { m_scale = scale; }
void Plane::setColor(const glm::vec4& col)     { m_color = col; }

void Plane::init()
{
    glEnable(GL_DEPTH_TEST);

    m_program = wolf::LoadShaders("data/wave.vsh", "data/wave.fsh");

    // Subdivision s gives 2^s quads per side, so s = 5 -> 32x32 quads (2048 triangles).
    // Chosen to meet the "at least 32x32" requirement.
    int numQuadsAxis = 1 << m_subdivisions; 
    int numVerticesPerAxis = numQuadsAxis + 1;

    // Generate grid vertices (XZ plane centered at origin)
    std::vector<Vertex> gridVertices(numVerticesPerAxis * numVerticesPerAxis);
    float step = 1.0f / numQuadsAxis;

    for (int z = 0; z < numVerticesPerAxis; ++z)
    {
        for (int x = 0; x < numVerticesPerAxis; ++x)
        {
            int idx = z * numVerticesPerAxis + x;
            gridVertices[idx].x = -0.5f + (x * step);
            gridVertices[idx].y = 0.0f;
            gridVertices[idx].z = -0.5f + (z * step);

            // Give grid a slight color tint
            gridVertices[idx].r = static_cast<GLubyte>(50 + (x * 200 / numVerticesPerAxis));
            gridVertices[idx].g = static_cast<GLubyte>(120 + (z * 130 / numVerticesPerAxis));
            gridVertices[idx].b = 255;
            gridVertices[idx].a = 255;
        }
    }

    // Build triangular mesh indices flat buffer
    std::vector<Vertex> triangleVertices;
    for (int z = 0; z < numQuadsAxis; ++z)
    {
        for (int x = 0; x < numQuadsAxis; ++x)
        {
            int topLeft     = z * numVerticesPerAxis + x;
            int topRight    = topLeft + 1;
            int bottomLeft  = (z + 1) * numVerticesPerAxis + x;
            int bottomRight = bottomLeft + 1;

            // Triangle 1
            triangleVertices.push_back(gridVertices[topLeft]);
            triangleVertices.push_back(gridVertices[topRight]);
            triangleVertices.push_back(gridVertices[bottomRight]);

            // Triangle 2
            triangleVertices.push_back(gridVertices[topLeft]);
            triangleVertices.push_back(gridVertices[bottomRight]);
            triangleVertices.push_back(gridVertices[bottomLeft]);
        }
    }

    m_vertexCount = static_cast<GLsizei>(triangleVertices.size());

    // GPU allocation
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, triangleVertices.size() * sizeof(Vertex), triangleVertices.data(), GL_STATIC_DRAW);

    int posAttr = glGetAttribLocation(m_program, "a_position");
    int colorAttr = glGetAttribLocation(m_program, "a_color");

    if (posAttr != -1)
    {
        glVertexAttribPointer(posAttr, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));
        glEnableVertexAttribArray(posAttr);
    }

    if (colorAttr != -1)
    {
        glVertexAttribPointer(colorAttr, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, r));
        glEnableVertexAttribArray(colorAttr);
    }

    glBindVertexArray(0);
}

void Plane::update(float dt)
{
    m_totalTime += dt;
}

void Plane::render(const glm::mat4& view, const glm::mat4& proj)
{
    glUseProgram(m_program);

    glm::mat4 mWorld = glm::mat4(1.0f);
    mWorld = glm::translate(mWorld, m_position);
    mWorld = glm::rotate(mWorld, m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    mWorld = glm::rotate(mWorld, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    mWorld = glm::rotate(mWorld, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    mWorld = glm::scale(mWorld, m_scale);

    int worldLoc = glGetUniformLocation(m_program, "world");
    int viewLoc  = glGetUniformLocation(m_program, "view");
    int projLoc  = glGetUniformLocation(m_program, "projection");
    int timeLoc  = glGetUniformLocation(m_program, "u_time");

    if (worldLoc != -1) glUniformMatrix4fv(worldLoc, 1, GL_FALSE, &mWorld[0][0]);
    if (viewLoc  != -1) glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    if (projLoc  != -1) glUniformMatrix4fv(projLoc, 1, GL_FALSE, &proj[0][0]);
    if (timeLoc  != -1) glUniform1f(timeLoc, m_totalTime);

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);

    glBindVertexArray(0);
    glUseProgram(0);
}