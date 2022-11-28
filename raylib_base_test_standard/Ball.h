#pragma once
#include "Player.h"
class Ball
{
public:
	float x;
	float y;
	int width;
	int height;

	//vec
	float dy;
	float dx;

	Ball(float X, float Y,int Width,int Height, float DY, float DX);
	~Ball();

	bool Collides(Player player);
	void reset();
	void update(float dt);
	void render();

};