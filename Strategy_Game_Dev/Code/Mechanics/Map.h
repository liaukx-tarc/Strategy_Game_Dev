#ifndef MAP
#define MAP

#include <d3dx9.h>

class Map
{
private:
	RECT tileRect;
	D3DXVECTOR3 pos;
	D3DXVECTOR2 tileSelected;

	float scrollTimer;

public:
	Map();
	~Map();

	void Draw();
	void MapScrolling();
};

#endif // !MAP