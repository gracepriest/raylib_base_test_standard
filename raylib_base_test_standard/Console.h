#pragma once
//a singleton to this class because will only need one per app
class HandleConsole
{
public:
	HandleConsole();
	void HideConsole();
	void ShowConsole();
	bool IsConsoleVisible();
	~HandleConsole();

};