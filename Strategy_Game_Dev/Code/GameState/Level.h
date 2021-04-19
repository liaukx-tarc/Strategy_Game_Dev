#ifndef LEVEL
#define LEVEL

#include "GameState.h"

class Level : public GameState
{
public:
	void init();
	void update();
	void fixUpdate();
	void draw();
	void release();
};

#endif // !GAMESTATE