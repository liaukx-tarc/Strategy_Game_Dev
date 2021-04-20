#include "GameStateManager.h"
#include "../GameState/Level.h"

//singleton
GameStateManager* GameStateManager::sInstance = NULL;

GameStateManager* GameStateManager::GetInstance()
{
	if (GameStateManager::sInstance == NULL)
	{
		sInstance = new GameStateManager;
	}

	return sInstance;
}

void GameStateManager::ReleaseInstance()
{
	delete sInstance;
	sInstance = NULL;
}

GameStateManager::GameStateManager()
{
	currentState = 0;
	preState = 0;

	g_Timer = new G_Timer();
	g_Timer->init(GAME_FPS);

	GameState* level = new Level();
	level->Init();
	stateList.push_back(level);
}

GameStateManager::~GameStateManager()
{
	stateList[currentState]->Release();

	for (int i = 0; i < stateList.size(); i++)
	{
		delete stateList[i];
		stateList[i] = NULL;
	}

	delete g_Timer;
}

void GameStateManager::Update()
{
	stateList[currentState]->Update();

	framesToUpdate = g_Timer->framesToUpdate();

	if (currentState == preState)
	{
		for (int i = 0; i < framesToUpdate; i++)
		{
			stateList[currentState]->FixUpdate();
		}
	}

	else
	{
		stateList[currentState]->Init();
		stateList[preState]->Release();
	}
}

void GameStateManager::Draw()
{
	if (currentState == preState)
	{
		stateList[currentState]->Draw();
	}

	else
	{
		preState = currentState;
	}
}