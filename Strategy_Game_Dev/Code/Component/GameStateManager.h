#ifndef GAMESTATEMANAGER
#define GAMESTATEMANAGER
#include <stdio.h>
#include <string>
#include <vector>

#include "G_Timer.h"
#include "../GameState/GameState.h"

#define GAME_FPS 60

class GameStateManager
{
private:
	static GameStateManager* sInstance;
	GameStateManager();
	~GameStateManager();

	G_Timer * g_Timer;

	int currentState, preState;
	float framesToUpdate;
	std::vector<GameState*> stateList;

public:
	static GameStateManager* GetInstance();
	static void ReleaseInstance();

	void Update();
	void Draw();
};

#endif // !GAMESTATEMANAGER