#pragma once
#include "States.h"
#include "Input.h"
#include <stack>


template <typename T>
class StackFSM
{
    //typedef std::stack<void*>(*ptR)();           //not needed
    //typedef ptR(*pm)();

public:
    std::stack<T> GameState;                     // function pointer declaration  
    T currentStateFunction;

    StackFSM()
    {

    }
    ~StackFSM()
    {

    }
    T getCurrentState()
    {

        return GameState.top();
    }


    void update()
    {
        //will be called in the game loop to update state
        //void (*currentStateFunction)();
        
        if (!GameState.empty())
        {
             currentStateFunction = getCurrentState();
        }
        else
        {
            this->pushState(GameStates::START_GAME);
        }



       
            if (IsKeyPressed(KEY_ENTER) and currentStateFunction == GameStates::START_GAME)
            {

                //stackPtr.popState();            //remove the screen screen
                this->pushState(GameStates::SERVE);  //push the second screen

            }
            else if (IsKeyPressed(KEY_ENTER) and currentStateFunction == GameStates::SERVE)
            {

                //stackPtr.popState();            //remove the screen screen
                this->pushState(GameStates::PLAY);    //push the second screen

            }

    }


    void popState()
    {
        return GameState.pop();
    }

    void pushState(T state)
    {
        if (GameState.empty())
        {
            GameState.push(state);
        }
        else if (getCurrentState() != state)
        {
            GameState.push(state);
        }
    }

};
