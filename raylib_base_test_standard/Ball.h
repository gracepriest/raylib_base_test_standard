#pragma once

class Ball
{
public:
	int x;
	int y;
	int width;
	int height;

	//vec
	double dy;
	double dx;

	Ball(int X, int Y,int Width,int Height, double DY, double DX);
	~Ball();

	bool Collides();
	void reset();
	void update(double dt);
	void render();

};