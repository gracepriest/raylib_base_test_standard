#include "Player.h"
#include "Color.h"
#include <algorithm> 

Player::Player(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->dy = 0;
	this->dx = 0;
	this->ai = false;

}

int newMax(int a, float b)
{
	if (a > b)
		return a;
	else 
		return round(b);

}

int newMin(int a ,float b)
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
		this->y = newMax(0, this->y + this->dy * deltaTime /60);
	}
		else 
		{
		this->y = newMin(GetScreenHeight() - this->height, this->y + this->dy * deltaTime / 60);
		}
	
	

}

void Player::Render()
{
	DrawRectangle(this->x, this->y, this->width,this->height, RAYWHITE);
}

Player::~Player()
{

}