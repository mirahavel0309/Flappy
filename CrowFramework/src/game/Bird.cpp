#include "Bird.h"

Bird::Bird(float startX_, float startY_, float width, float height)
    : startX(startX_), startY(startY_),
    cx(startX_), cy(startY_),
    w(width), h(height),
    velocityY(0.0f)
{
    startX = startX_;
    startY = startY_;

    w = width;
    h = height;

    Reset();
}

void Bird::Reset()
{
    cx = startX;
    cy = startY;
    velocityY = 0.0f;
}

void Bird::Update(float dt)
{
    velocityY += mGravity * dt;
    cy += velocityY * dt;
}

void Bird::Flap()
{
    velocityY = mFlapStrength;
}

AABB Bird::GetAABB() const
{
    return AABB::FromCenterHalfSize(cx, cy, w * 0.5f, h * 0.5f);
}
