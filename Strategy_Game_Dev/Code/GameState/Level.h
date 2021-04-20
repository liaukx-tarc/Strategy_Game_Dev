#ifndef LEVEL
#define LEVEL

#include "GameState.h"
#include "../Mechanics/Map.h"

class Level : public GameState
{
private:
	Map map;

public:
	void Init();
	void Update();
	void FixUpdate();
	void Draw();
	void Release();
};

#endif // !GAMESTATE