#pragma once

class Pipe
{
public:
    Pipe(float startX, float startY, float width, float height, float speedX);

    void Update(float dt);
    void WrapIfNeeded(float killX, float respawnX);

    float GetX() const { return cx; }
    float GetY() const { return cy; }
    float GetW() const { return w; }
    float GetH() const { return h; }

private:
    float cx;
    float cy;
    float w;
    float h;
    float speedX;
};
