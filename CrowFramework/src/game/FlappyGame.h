#pragma once

#include "engine/AABB.h"
#include "engine/graphics/Shader.h"
#include "Bird.h"
#include "PipePair.h"

struct FlappyConfig
{
    float worldTop = 1.0f;
    float worldBottom = -1.0f;

    float killX = -1.2f;
    float respawnX = 1.2f;

    // PipePair
    float pipeStartX = 1.2f;
    float pipeWidth = 0.25f;
    float pipeSpeed = 0.8f;

    float gapH = 0.45f;
    float minGapY = -0.5f;
    float maxGapY = 0.5f;

    // Bird
    float birdStartX = -0.3f;
    float birdStartY = 0.0f;
    float birdW = 0.15f;
    float birdH = 0.10f;
};

class FlappyGame
{
public:
    enum class State
    {
        Ready,   
        Playing,
        GameOver
    };

public:
    explicit FlappyGame(const FlappyConfig& cfg);

    void OnFlapPressed();

    void Update(float dt);
    void RenderWorld(Shader& shader, GLuint vao) const;

    void Reset();

    State GetState() const { return mState; }
    bool IsDebugDraw() const { return mDebugDraw; }
    void SetDebugDraw(bool v) { mDebugDraw = v; }

private:
    bool CheckWorldBounds(const AABB& birdBox) const;
    bool CheckPipeCollision(const AABB& birdBox) const;

private:
    FlappyConfig mCfg;

    Bird mBird;
    PipePair mPipes;

    State mState = State::Playing;
    bool mDebugDraw = true;

};
