#include "Ball.h"
#include "Color.h"


Ball::Ball(float X, float Y, int Width, int Height, float DY, float DX)
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
	this->x = GetScreenWidth() / 2 - 2;
	this->y = GetScreenHeight() / 2 - 2;
	this->dx = 0;
	this->dy = 0;
}

bool Ball::Collides(Player player)
{
	if (this->x > player.x + player.width or player.x > this->x + this->width)
		return false;
		
		// then check to see if the bottom edge of either is higher than the top
		// edge of the other

	if (this->y > player.y + player.height or player.y > this->y + this->height)
		return false;

	else
		// if the above aren't true, they're overlapping
		return true;
	
}

void Ball::update(float dt)
{
	this->x += this->dx *dt/100;
	
	this->y+= this->dy * dt/100;
}

void Ball::render()
{
	DrawRectangle(this->x ,this->y, 25, 25, MEANGREEN);
}

Ball::~Ball()
{
	
}