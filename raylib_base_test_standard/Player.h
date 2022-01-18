#pragma once

class Player
{
public:
    int x;
    int y;
    int width;
    int height;
    int dy;
    int dx;
    bool ai;

	Player(int x, int y, int width, int height);
	~Player();

    void Update(float detlaTime);
    void Render();


    


};