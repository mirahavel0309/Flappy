#include "PipePair.h"
#include <cstdlib>
#include <algorithm>

static float Rand01()
{
    return (float)std::rand() / (float)RAND_MAX;
}

static float RandRange(float a, float b)
{
    return a + (b - a) * Rand01();
}

PipePair::PipePair(float startX, float width, float speedX, float gapH, float minGapY, float maxGapY)
    : pipe(startX, 0.0f, width, 1.0f, speedX)
{
    this->gapH = gapH;
    this->minGapY = minGapY;
    this->maxGapY = maxGapY;

    RespawnGapY();
}

void PipePair::Update(float dt, float killX, float respawnX)
{
    float prevX = pipe.GetX();

    pipe.Update(dt);
    pipe.WrapIfNeeded(killX, respawnX);

    if (pipe.GetX() > prevX)
    {
        RespawnGapY();
    }
}

void PipePair::Render(Shader& shader, GLuint vao) const
{
    float x = pipe.GetX();
    float w = pipe.GetW();

    float gapTop = gapY + gapH * 0.5f;
    float gapBottom = gapY - gapH * 0.5f;

    float topH = 1.0f - gapTop;
    float topCy = (1.0f + gapTop) * 0.5f;

    float bottomH = gapBottom + 1.0f;
    float bottomCy = (-1.0f + gapBottom) * 0.5f;

    topH = std::max(0.0f, topH);
    bottomH = std::max(0.0f, bottomH);

    shader.SetVec2("uScale", w, topH);
    shader.SetVec2("uOffset", x, topCy);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    shader.SetVec2("uScale", w, bottomH);
    shader.SetVec2("uOffset", x, bottomCy);
    glDrawArrays(GL_TRIANGLES, 0, 6);

}

void PipePair::RespawnGapY()
{
    gapY = RandRange(minGapY, maxGapY);
}
