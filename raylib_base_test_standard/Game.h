#pragma once
//Use to create and control the game
#include "raylib.h"

class Game
{
public:
	int screenWidth;
	int screenHeight;

	
	
	void UpdateState();

	Game();
	
	//need a draw/render function
	void Draw();
	
	//load or init function 
	//return number greater than 0 if load fails
	int load();

	//update function that provides detla time
	void Update();

	//close or shutdow function
	void Close();

	//keypress function
	
	char CheckKeyPress();

	void Start();


	

	~Game();
	

	

};
