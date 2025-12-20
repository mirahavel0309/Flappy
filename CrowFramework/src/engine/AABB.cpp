#include "engine/AABB.h"

bool AABB::Intersects(const AABB& other) const
{
	if (right < other.left || left > other.right) return false;
	if (top < other.bottom || bottom > other.top) return false;

	return true;
}

AABB AABB::FromCenterHalfSize(float cx, float cy, float halfW, float halfH)
{
	AABB box;
	box.left = cx - halfW;
	box.right = cx + halfW;
	box.top = cy + halfH;
	box.bottom = cy - halfH;

	return box;
}