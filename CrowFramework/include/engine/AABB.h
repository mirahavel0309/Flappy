#pragma once
struct AABB
{
public:
	bool Intersects(const AABB& other) const;
	static AABB FromCenterHalfSize(float cx, float cy, float halfW, float halfH);

private:
	float left, right, top, bottom;
};

