//Class to handle all Console request
#include <Windows.h>
#include "Console.h"

    HandleConsole::HandleConsole()
    {

    }
    //handle closing and opening the console window
    void HandleConsole::HideConsole()
    {
        ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    }

    void HandleConsole::ShowConsole()
    {
        ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
    }

    bool HandleConsole::IsConsoleVisible()
    {
        return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
    }
    HandleConsole::~HandleConsole()
    {

    }
