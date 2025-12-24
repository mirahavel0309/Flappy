#pragma once
#include "Pipe.h"
#include "engine/graphics/Shader.h"

class PipePair
{
public:
    PipePair(float startX, float width, float speedX,
        float gapH, float minGapY, float maxGapY);

    void Update(float dt, float killX, float respawnX);
    void Render(Shader& shader, GLuint vao) const;

    float GetX() const { return pipe.GetX(); }
    float GetGapY() const { return gapY; }
    float GetGapH() const { return gapH; }
    float GetPipeW() const { return pipe.GetW(); }

private:
    Pipe pipe;
    float gapY = 0.0f;
    float gapH = 0.5f;
    float minGapY = -0.5f;
    float maxGapY = 0.5f;

    void RespawnGapY();
};
