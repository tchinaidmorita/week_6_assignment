#include "SamplePlane.h"

void SamplePlane::init()
{
    m_plane.init();
    m_plane.setScale(glm::vec3(4.0f, 1.0f, 4.0f)); // Enlarge grid so waves look clear
}

void SamplePlane::update(float dt)
{
    m_plane.update(dt);
}

void SamplePlane::render(int width, int height)
{
    glClearColor(0.05f, 0.05f, 0.08f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float aspect = (float)width / (float)height;
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
    
    // Position camera looking down slightly at an angle
    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 3.0f, 5.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    m_plane.render(view, proj);
}