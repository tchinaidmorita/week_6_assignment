#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

class ColorBlendOverTime: public Sample
{
public:
    ColorBlendOverTime(wolf::App* pApp) : Sample(pApp,"Blending between two colors over time, in a sin wave") {}
    ~ColorBlendOverTime();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    wolf::VertexBuffer* m_pVB = 0;
    wolf::VertexDeclaration* m_pDecl = 0;
    wolf::Program* m_pProgram = 0;
    float m_time = 0;
};