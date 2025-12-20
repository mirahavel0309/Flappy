#pragma once
struct AABB
{
	float left, right, top, bottom;

	bool Intersects(const AABB& other) const;
	static AABB FromCenterHalfSize(float cx, float cy, float halfW, float halfH);
};

