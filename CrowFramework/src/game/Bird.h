#pragma once
#include "engine/AABB.h"

class Bird
{
public:
    Bird(float startX, float startY, float width, float height);

    void Reset();
    void Update(float dt);
    void Flap();
    AABB GetAABB() const;

    float GetX() const { return cx; }
    float GetY() const { return cy; }
    float GetW() const { return w; }
    float GetH() const { return h; }

private:
    float startX;
    float startY;

    float cx;
    float cy;
    float w;
    float h;
    float velocityY = 0.0f;

    const float mGravity = -1.2f;
    const float mFlapStrength = 1.0f;
};