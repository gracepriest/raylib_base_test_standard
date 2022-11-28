#include "Player.h"
#include "Color.h"
#include <algorithm> 

Player::Player(float x, float y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->dy = 0;
	this->dx = 0;
	this->ai = false;

}

float newMax(int a, float b)
{
	if (a > b)
		return a;
	else 
		return round(b);

}

float newMin(int a ,float b)
{
	if (a < b)
		return a;
	else
		return round(b);

}

void Player::Update(float deltaTime)
{
	if (this->dy < 0)
	{
		this->y = newMax(0, this->y + this->dy * deltaTime );
	}
		else 
		{
		this->y = newMin(GetScreenHeight() - this->height, this->y + this->dy * deltaTime);
		}
	
	

}

void Player::Render()
{
	DrawRectangle(this->x, this->y, this->width,this->height, RAYWHITE);
}

Player::~Player()
{

}