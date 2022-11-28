#pragma once

class Player
{
public:
    float x;
    float y;
    int width;
    int height;
    float dy;
    float dx;
    bool ai;

	Player(float x, float y, int width, int height);
	~Player();

    void Update(float detlaTime);
    void Render();


    


};