#pragma once
#include "../samplefw/Sample.h"
#include "Plane.h"

class SamplePlane : public Sample
{
public:
    SamplePlane(wolf::App* pApp) : Sample(pApp, "SamplePlane")
    {
        init();
    }
    
    ~SamplePlane() {}

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    Plane m_plane{5};
};