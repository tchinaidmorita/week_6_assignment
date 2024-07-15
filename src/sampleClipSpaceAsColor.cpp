#include "sampleClipSpaceAsColor.h"
#include "../samplefw/Grid2D.h"

struct Vertex
{
	GLfloat x,y;
};

static const Vertex gs_squareVertices[] = {
	{ -100.0f, -100.0f }, 
	{ -100.0f, 100.0f }, 
	{ 100.0f, 100.0f }, 

	{ 100.0f, 100.0f }, 
	{ 100.0f, -100.0f }, 
	{ -100.0f, -100.0 }, 
};

ClipSpaceAsColor::~ClipSpaceAsColor()
{
	printf("Destroying Clip Space as Color Sample\n");
	delete m_pDecl;
	wolf::ProgramManager::DestroyProgram(m_pProgram);
	wolf::BufferManager::DestroyBuffer(m_pVB);
}

void ClipSpaceAsColor::init()
{
    // Only init if not already done
    if(!m_pProgram)
    {
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		m_pProgram = wolf::ProgramManager::CreateProgram("data/clipSpaceAsColor.vsh", "data/clipSpaceAsColor.fsh");
		m_pVB = wolf::BufferManager::CreateVertexBuffer(gs_squareVertices, sizeof(Vertex) * 6);

		m_pDecl = new wolf::VertexDeclaration();
		m_pDecl->Begin();
		m_pDecl->AppendAttribute(wolf::AT_Position, 2, wolf::CT_Float);
		m_pDecl->SetVertexBuffer(m_pVB);
		m_pDecl->End();
	}
	
    printf("Successfully initialized Clip Space as Color Sample\n");
}

void ClipSpaceAsColor::update(float dt) 
{
}

void ClipSpaceAsColor::render(int width, int height)
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 mProj = glm::ortho(0.0f,(float)width,(float)height,0.0f,0.0f,1000.0f);
    glm::mat4 mView(1.0f);
    glm::mat4 mWorld(1.0f);

	glm::vec2 mousePos = m_pApp->getMousePos();
	mWorld = glm::translate(glm::vec3(mousePos.x, mousePos.y, 0.0f));

    // Use shader program.
	m_pProgram->Bind();
    
	// Bind Uniforms
    m_pProgram->SetUniform("projection", mProj);
    m_pProgram->SetUniform("view", mView);
    m_pProgram->SetUniform("world", mWorld);
    
	// Set up source data
	m_pDecl->Bind();

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
