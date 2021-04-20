#ifndef DATA_CENTER
#define DATA_CENTER

#include <d3dx9.h>
#include <string>

//Map
#define MAX_MAP_X 50
#define MAX_MAP_Y 50
#define TILE_WIDTH	64
#define TILE_HEIGHT	64

class DataCenter
{
private:
	static DataCenter* sInstance;
	DataCenter();
	~DataCenter();

	HRESULT hr[3];

public:
	//Singleton
	static DataCenter * GetInstance();
	static void ReleaseInstance();

	//Draw
	LPD3DXSPRITE sprite;
	D3DXVECTOR2 screenPos;

		//Map
		LPDIRECT3DTEXTURE9 tileSet;

		int tileMap[MAX_MAP_Y][MAX_MAP_X];
		int pathMap[MAX_MAP_Y][MAX_MAP_X];

		//Unit
		LPDIRECT3DTEXTURE9 unitSet;

	void Inti();
	void Release();
	void LoadData(std::string name);
};

#endif // !DATA_CENTER