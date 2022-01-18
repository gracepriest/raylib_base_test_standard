#include "Game.h"
#include "raylib.h"
#include "Ball.h"
#include "Player.h"
#include "StackFSM.h"
Ball * ball;
//player objectS
Player *player1;
Player *player2;
StackFSM<GameStates> * FSM;
float dt;

int Game::load()
{
   ball = new Ball(150, 250, 15, 15, 0, 0);
   player1 = new Player(10, 30, 15, 45);
   player2 = new Player(1250, 650, 15, 45);
   FSM = new StackFSM<GameStates>();
    // Initialization
    //--------------------------------------------------------------------------------------
    this->screenWidth = 1280;
    this->screenHeight = 720;

  

    InitWindow(screenWidth, screenHeight, "Pong C++");

    


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    //return 0 if initWindows works
    
    return 0;
}

int IsKeyPress()
{
    return 0;
    
}
void Game::Update()
{
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        dt = GetFrameTime();
       
        
        // TODO: Update your variables here
        FSM->update();

        // TODO :check of keypress
        if (FSM->GameState.top() == GameStates::SERVE)
        {
            if (IsKeyDown(KEY_UP))
            {
                player1->dy = -200;
            }
            else if (IsKeyDown(KEY_DOWN))
            {
                player1->dy = 200;

            }
            else
            {
                player1->dy = 0;
            }
            
        }
        
        player1->Update(dt+1);
        // Draw
           Draw();
           
    }

}
void Game::Draw()
{
    BeginDrawing();

   
    
    ClearBackground(Color{ 0,0,0,255 });

    ball->render();
   
    
    if (FSM->getCurrentState() == GameStates::START_GAME)
    {
        DrawText("WELCOME TO PONG!", this->screenHeight / 2 + 130, 0, 30, LIGHTGRAY);
        DrawText("PRESS ENTER TO BEGIN", this->screenHeight / 2 + 130, 40, 30, LIGHTGRAY);
    }
    else if (FSM->getCurrentState() == GameStates::SERVE)
    {
        DrawText("WELCOME TO PONG!", this->screenHeight / 2 + 130, 0, 30, LIGHTGRAY);
        DrawText("PLAYER 1 SERVE'S", this->screenHeight / 2 + 130, 40, 30, LIGHTGRAY);
        
    }
    player1->Render();
    player2->Render();
  
    EndDrawing();
}


Game::Game()
{

}

Game::~Game()
{
    delete ball;
    ball = nullptr;
    delete player1;
    player1 = nullptr;
    delete player2;
    player2 = nullptr;
    delete FSM;
    FSM = nullptr;
}

void Game::Start()
{
   
    load();
    Update();
}