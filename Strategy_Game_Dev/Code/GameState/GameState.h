#ifndef GAMESTATE
#define GAMESTATE

class GameState
{
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void FixUpdate() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;
};

#endif // !GAMESTATE