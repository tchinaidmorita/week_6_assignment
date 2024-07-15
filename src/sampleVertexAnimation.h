#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

class VertexAnimation: public Sample
{
public:
    VertexAnimation(wolf::App* pApp) : Sample(pApp,"Demonstrating very simple vertex animation in shader") {}
    ~VertexAnimation();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    wolf::VertexBuffer* m_pVB = 0;
    wolf::VertexDeclaration* m_pDecl = 0;
    wolf::Program* m_pProgram = 0;
    float m_time = 0;
};