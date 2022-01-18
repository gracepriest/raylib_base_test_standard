#include "Ball.h"
#include "Color.h"


Ball::Ball(int X, int Y, int Width, int Height, double DY, double DX)
{
	this->x = 1280 / 2; 
	this->y = 720 / 2;
	this->width = Width;
	this->height = Height;
	this->dx = DX;
	this->dy = DY;

}

void Ball::reset()
{

}

bool Ball::Collides()
{
	return 0;
}

void Ball::update(double dt)
{
	this->x =+ this->dx * dt;
	this->y =+ this->dy * dt;
}

void Ball::render()
{
	DrawRectangle(this->x ,this->y, 25, 25, MEANGREEN);
}

Ball::~Ball()
{
	
}