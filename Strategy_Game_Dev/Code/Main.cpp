#include "Component/G_Windows.h"
#include "Component/Graphic.h"
#include "Component/DInput.h"
#include "Component/GameStateManager.h"

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) //App only
int main()	//App and Console
{
	//create windows
	GWindows::GetInstance()->CreateWindows();
	DInput::GetInstance()->CreateInput();
	Graphic::GetInstance()->CreateGraphic();

	GameStateManager::GetInstance();

	while (GWindows::GetInstance()->WindowsLoop())
	{
		DInput::GetInstance()->InputLoop();
		GameStateManager::GetInstance()->Update();

		Graphic::GetInstance()->GraphicLoopStart();
		GameStateManager::GetInstance()->Draw();
		Graphic::GetInstance()->GraphicLoopEnd();

		GWindows::GetInstance()->keyPress = 0;
	}

	//delete the class and clear
	
	GameStateManager::GetInstance()->ReleaseInstance();
	Graphic::GetInstance()->ReleaseInstance();
	DInput::GetInstance()->ReleaseInstance();
	GWindows::GetInstance()->ReleaseInstance();

	return 0;
}