#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

class ClipSpaceAsColor: public Sample
{
public:
    ClipSpaceAsColor(wolf::App* pApp) : Sample(pApp,"Using Clip Space coords as colors") {}
    ~ClipSpaceAsColor();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    wolf::VertexBuffer* m_pVB = 0;
    wolf::VertexDeclaration* m_pDecl = 0;
    wolf::Program* m_pProgram = 0;
};