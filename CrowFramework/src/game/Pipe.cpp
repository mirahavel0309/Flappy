#include "Pipe.h"

Pipe::Pipe(float startX, float startY, float width, float height, float speed)
{
	cx = startX;
	cy = startY;
	w = width;
	h = height;
	speedX = speed;
}

void Pipe::Update(float dt)
{
	cx -= speedX * dt;
}

void Pipe::WrapIfNeeded(float killX, float respawnX)
{
	if (cx + w * 0.5f < killX)
	{
		cx = respawnX + w * 0.5f;
	}
}
