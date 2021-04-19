#ifndef GRAPHIC
#define GRAPHIC
#include <d3d9.h>
#include <d3dx9.h>

#define BUFFER_WIDTH 1920
#define BUFFER_HEIGHT 1080

class Graphic
{
private:
	static Graphic* sInstance;
	Graphic();
	~Graphic();

	HRESULT hr[4];

	D3DPRESENT_PARAMETERS d3dPP;
	IDirect3D9 * direct3D9;

	LPD3DXSPRITE sprite;
	LPDIRECT3DTEXTURE9 cursorTexture;
	LPDIRECT3DTEXTURE9 hammerTexture;
	RECT cursorRect;

	D3DXVECTOR2 scaling;
	D3DXMATRIX mat;

public:
	//Singleton
	static Graphic * GetInstance();
	static void ReleaseInstance();

	IDirect3DDevice9 * d3dDevice;

	//Graphic Function
	void CreateGraphic();
	void GraphicLoopStart();
	void GraphicLoopEnd();

	void DrawCursor();
};

#endif // !GRAPHIC