#include "sampleVertexAnimation.h"
#include "../samplefw/Grid2D.h"

struct Vertex
{
	GLfloat x,y;
};

const int NUM_SEGMENTS = 50;
const float STARTX = -200.0f;
const float SEGMENT_WIDTH = (2.0f * -STARTX) / NUM_SEGMENTS;

static const Vertex gs_squareVertices[] = {
	{ 0.0f, -100.0f }, 
	{ 0.0f, 100.0f }, 
	{ SEGMENT_WIDTH, 100.0f }, 

	{ SEGMENT_WIDTH, 100.0f }, 
	{ SEGMENT_WIDTH, -100.0f }, 
	{ 0.0f, -100.0 }, 
};

VertexAnimation::~VertexAnimation()
{
	printf("Destroying Vertex Animation Sample\n");
	delete m_pDecl;
	wolf::ProgramManager::DestroyProgram(m_pProgram);
	wolf::BufferManager::DestroyBuffer(m_pVB);
}

void VertexAnimation::init()
{
    // Only init if not already done
    if(!m_pProgram)
    {
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		Vertex* pAllVerts = new Vertex[NUM_SEGMENTS * 6];
		float x = STARTX;
		int vertIdx = 0;
		for(int i = 0; i < NUM_SEGMENTS; i++)
		{
			for(int j = 0; j < 6; j++)
			{
				pAllVerts[vertIdx].x = x + gs_squareVertices[j].x;
				pAllVerts[vertIdx].y = gs_squareVertices[j].y;
				vertIdx++;
			}	

			x += SEGMENT_WIDTH;
		}
		m_pProgram = wolf::ProgramManager::CreateProgram("data/vertexAnimation.vsh", "data/vertexAnimation.fsh");
		m_pVB = wolf::BufferManager::CreateVertexBuffer(pAllVerts, sizeof(Vertex) * 6 * NUM_SEGMENTS);

		m_pDecl = new wolf::VertexDeclaration();
		m_pDecl->Begin();
		m_pDecl->AppendAttribute(wolf::AT_Position, 2, wolf::CT_Float);
		m_pDecl->SetVertexBuffer(m_pVB);
		m_pDecl->End();

		delete[] pAllVerts;
	}
	
	m_time = 0.0f;
    printf("Successfully initialized Vertex Animation Sample\n");
}

void VertexAnimation::update(float dt) 
{
	m_time += dt;
}

void VertexAnimation::render(int width, int height)
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 mProj = glm::ortho(0.0f,(float)width,(float)height,0.0f,0.0f,1000.0f);
    glm::mat4 mView(1.0f);
    glm::mat4 mWorld(1.0f);

	mWorld = glm::translate(glm::vec3((float)width / 2.0f, (float)height / 2.0f, 0.0f));

    // Use shader program.
	m_pProgram->Bind();
    
	// Bind Uniforms
    m_pProgram->SetUniform("projection", mProj);
    m_pProgram->SetUniform("view", mView);
    m_pProgram->SetUniform("world", mWorld);

    m_pProgram->SetUniform("u_time", m_time);
    
	// Set up source data
	m_pDecl->Bind();

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, 6 * NUM_SEGMENTS);
}
