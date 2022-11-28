#include "Game.h"
#include "raylib.h"
#include "Ball.h"
#include "Player.h"
#include "StackFSM.h"
#include <stdlib.h>
#include <time.h>  
#include <string>

//ball object
Ball * ball;

//player objects
Player *player1;
Player *player2;

//State Machine
StackFSM<GameStates> * FSM;

//delta time
float dt =0;

int servingPlayer = 1;
int player1Score = 0;
int player2Score = 0;
int winningPlayer = 0;
bool startflag = true;

Sound scoreSound;
Sound paddleSound;
Sound wall_hitSound;

Music  gameMusic;

//init sound




int Game::load()
{
   
   //add wav files
   

   ball = new Ball(150, 250, 15, 15, 0, 0);
   player1 = new Player(10, 30, 15, 60);
   player2 = new Player(1250, 350, 15, 60);
   FSM = new StackFSM<GameStates>();
    // Initialization
    //--------------------------------------------------------------------------------------
    this->screenWidth = 1280;
    this->screenHeight = 720;

  

    InitWindow(screenWidth, screenHeight, "Pong C++");
    InitAudioDevice();
    scoreSound = LoadSound("score.wav");
    paddleSound = LoadSound("paddle_hit.wav");
    wall_hitSound = LoadSound("wall_hit.wav");
    gameMusic = LoadMusicStream("marios_way.mp3");

    PlayMusicStream(gameMusic);
    //PlaySound(scoreSound);
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
   
    float temp = 0;
    float frame_Passed = 0;

    //add const for number this->screenHeight / 2 + 130

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateMusicStream(gameMusic);
        SetMusicPitch(gameMusic, 1.0f);
      
        frame_Passed = GetFrameTime();
        if (dt < 0.9)
        {
            dt += frame_Passed;

        }
        else
        {
            dt = 0.9;
        }
       
        // TODO: Update your variables here
        FSM->update();
        
        //random seed
        srand(time(NULL));

        // TODO :check of keypress
        if (FSM->getCurrentState() == GameStates::PLAY)
        {
            if (IsKeyDown(KEY_ENTER) and startflag == true)
            {
                startflag = false;
                if (servingPlayer == 1)
                {
                    ball->dx = 640;
                }
                else
                {
                    ball->dx = -640;
                }
            }

            if (IsKeyDown(KEY_UP))
            {
                player1->dy = -5;
            }
            else if (IsKeyDown(KEY_DOWN))
            {
                player1->dy = 5;

            }
            else
            {
                player1->dy = 0;
            }

            if (IsKeyDown(KEY_W))
            {
                player2->dy = -5;
            }
            else if (IsKeyDown(KEY_S))
            {
                player2->dy = 5;

            }
            else
            {
                player2->dy = 0;
            }

            if (IsKeyDown(KEY_F1))
            {
                if (servingPlayer == 1)
                {
                    ball->dx = 640;
                }
                else
                {
                    ball->dx = -640;
                }
            }
            


            player1->Update(dt);
            player2->Update(dt);
            ball->update(dt);


            // detect ball collision with paddles
            if (ball->Collides(*player2))
            {
                DrawText("HIT", this->screenHeight / 2 + 130, 80, 30, LIGHTGRAY);
                PlaySound(paddleSound);
                PlayMusicStream(gameMusic);

                ball->dx = -ball->dx * 1.03;
                ball->x = player2->x - 15;

                if (ball->dy < 0)
                {
                    ball->dy = -rand() % 350 + 10;
                }
                else
                {
                    ball->dy = rand() % 350 + 10;
                }
            }
            else if (ball->Collides(*player1))
            {
                DrawText("HIT", this->screenHeight / 2 + 130, 80, 30, LIGHTGRAY);
                PlaySound(paddleSound);
                ball->dx = -ball->dx * 1.03;
                ball->x = player1->x + 15;

                if (ball->dy < 0)
                {
                    ball->dy = -rand() % 350 + 10;
                }
                else
                {
                    ball->dy = rand() % 350 + 10;
                }
            }

            //detect upper screen boundary

            if (ball->y <= 0)
            {
                ball->y = 0;
                ball->dy = -ball->dy;
                
                
                //TO DO: play sound here
                PlaySound(wall_hitSound);
            }

            // detect lower screen boundary

            if (ball->y >= this->screenHeight - 28)
            {
                ball->y = this->screenHeight - 28;
                ball->dy = -ball->dy;
                PlaySound(wall_hitSound);

            
            }

            //CHECK IF WE REACH THE LEFT SIDE OF THE SCREEN
            if (ball->x < 0)
            {
                //player 2 scored set player 1 to serve
                servingPlayer = 1;
                player2Score++;
                //TO DO: add code to play sound
                PlaySound(scoreSound);

                if (player2Score == 10)
                {
                    winningPlayer = 2;
                    FSM->pushState(GameStates::WIN);
                }
                else
                {
                    FSM->pushState(GameStates::SERVE);
                    ball->reset();
                    startflag = true;
                }


            }

            //CHECK IF WE REACK THE RIGHT SIDE OF THE SCREEN
            if (ball->x > this->screenWidth)
            {
                servingPlayer = 2;
                player1Score++;
                //TO DO: add code for sound
                PlaySound(scoreSound);
                //TO Do: add code for AI
                if (player1Score == 10)
                {
                    winningPlayer = 1;
                    FSM->pushState(GameStates::WIN);
                }
                else
                {
                    FSM->pushState(GameStates::SERVE);
                    ball->reset();
                    startflag = true;
                }


            }
        }

        if (IsKeyDown(KEY_F2) and FSM->getCurrentState() == GameStates::WIN)
        {
            player1Score = 0;
            player2Score = 0;
            ball->reset();
            startflag = true;
            FSM->pushState(GameStates::SERVE);
        }

        // Draw
           Draw();

           
    }

}


void Game::UpdateState()
{
    
    
}
void Game::Draw()
{
    BeginDrawing();

    ClearBackground(Color{ 0,0,0,255 });
    std::string player1score = std::to_string(player1Score);
    std::string player2score = std::to_string(player2Score);

    DrawText(player1score.c_str(), this->screenWidth / 2 - 150, 160, 100, LIGHTGRAY);
    DrawText(player2score.c_str(), 850 , 160, 100, LIGHTGRAY);
   
    
    if (FSM->getCurrentState() == GameStates::START_GAME)
    {
        DrawText("WELCOME TO PONG!", this->screenWidth / 2 -150, 0, 30, LIGHTGRAY);
        DrawText("PRESS ENTER TO BEGIN", this->screenWidth / 2 -150 , 40, 30, LIGHTGRAY);
    }
    else if (FSM->getCurrentState() == GameStates::SERVE)
    {
        DrawText("WELCOME TO PONG!", this->screenHeight / 2 + 130, 0, 30, LIGHTGRAY);
        std::string s = "PLAYER " + std::to_string(servingPlayer);
        s.append(" SERVE'S");
        DrawText(s.c_str(), this->screenHeight / 2 + 130, 40, 30, LIGHTGRAY);
        
    }
    else if (FSM->getCurrentState() == GameStates::PLAY)
    {
       // DrawText("playing!", this->screenHeight / 2 + 130, 0, 30, LIGHTGRAY);
    }
    else if (FSM->getCurrentState() == GameStates::WIN)
    {
        std::string tempWin = "PLAYER 2 WINNERS " + std::to_string(winningPlayer);
        DrawText(tempWin.c_str(), this->screenHeight / 2 + 130, 0, 30, LIGHTGRAY);
        DrawText("Press F2 TO RESTART THE GAME \nOR ESC TO QUIT!", this->screenHeight / 2 + 130, 40, 30, LIGHTGRAY);
        
    }

    ball->render();
    player1->Render();
    player2->Render();
    
    EndDrawing();
}


Game::Game()
{
    this->screenWidth = 0;
    this->screenHeight = 0;
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
    CloseAudioDevice();
}

void Game::Start()
{
   
    load();
    UpdateState();
    Update();
}