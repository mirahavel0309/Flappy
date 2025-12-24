#include "FlappyGame.h"

FlappyGame::FlappyGame(const FlappyConfig& cfg)
    : mCfg(cfg)
    , mBird(cfg.birdStartX, cfg.birdStartY, cfg.birdW, cfg.birdH)
    , mPipes(cfg.pipeStartX, cfg.pipeWidth, cfg.pipeSpeed,
        cfg.gapH, cfg.minGapY, cfg.maxGapY)
{
    mState = State::Playing;
}

void FlappyGame::OnFlapPressed()
{
    if (mState == State::Playing)
    {
        mBird.Flap();
    }
    else if (mState == State::GameOver)
    {
        Reset();
        mBird.Flap();
    }
}

void FlappyGame::Update(float dt)
{
    if (dt <= 0.0f) return;
    if (mState != State::Playing) return;

    mBird.Update(dt);
    mPipes.Update(dt, mCfg.killX, mCfg.respawnX);

    AABB birdBox = mBird.GetAABB();

    if (CheckWorldBounds(birdBox))
    {
        mState = State::GameOver;
        return;
    }

    if (CheckPipeCollision(birdBox))
    {
        mState = State::GameOver;
        return;
    }
}

void FlappyGame::RenderWorld(Shader& shader, GLuint vao) const
{
    shader.Use();
    glBindVertexArray(vao);

    // Bird
    shader.SetVec3("uColor", 0.0f, 1.0f, 0.0f);
    shader.SetVec2("uScale", mBird.GetW(), mBird.GetH());
    shader.SetVec2("uOffset", mBird.GetX(), mBird.GetY());
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Pipes
    shader.SetVec3("uColor", 0.2f, 0.8f, 1.0f);
    mPipes.Render(shader, vao);

    if (mDebugDraw)
    {
        AABB b = mBird.GetAABB();
        float bCx = (b.left + b.right) * 0.5f;
        float bCy = (b.bottom + b.top) * 0.5f;
        float bW = (b.right - b.left);
        float bH = (b.top - b.bottom);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        shader.SetVec3("uColor", 1.0f, 0.0f, 0.0f);
        shader.SetVec2("uScale", bW, bH);
        shader.SetVec2("uOffset", bCx, bCy);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    glBindVertexArray(0);
}

void FlappyGame::Reset()
{
    mBird.Reset();
    mPipes = PipePair(mCfg.pipeStartX, mCfg.pipeWidth, mCfg.pipeSpeed,
        mCfg.gapH, mCfg.minGapY, mCfg.maxGapY);

    mState = State::Playing;
}

bool FlappyGame::CheckWorldBounds(const AABB& birdBox) const
{
    if (birdBox.top > mCfg.worldTop) return true;
    if (birdBox.bottom < mCfg.worldBottom) return true;
    return false;
}

bool FlappyGame::CheckPipeCollision(const AABB& birdBox) const
{
    float gapY = mPipes.GetGapY();
    float gapH = mPipes.GetGapH();

    float gapTop = gapY + gapH * 0.5f;
    float gapBottom = gapY - gapH * 0.5f;

    float x = mPipes.GetX();
    float w = mPipes.GetPipeW();

    float topH = mCfg.worldTop - gapTop;
    float topCy = (mCfg.worldTop + gapTop) * 0.5f;
    AABB topBox = AABB::FromCenterHalfSize(x, topCy, w * 0.5f, topH * 0.5f);

    float bottomH = gapBottom - mCfg.worldBottom;
    float bottomCy = (mCfg.worldBottom + gapBottom) * 0.5f;
    AABB bottomBox = AABB::FromCenterHalfSize(x, bottomCy, w * 0.5f, bottomH * 0.5f);

    return birdBox.Intersects(topBox) || birdBox.Intersects(bottomBox);
}
