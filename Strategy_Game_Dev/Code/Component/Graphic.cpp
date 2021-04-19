#include "Graphic.h"
#include "G_Windows.h"

#include <stdio.h>

//Singleton
Graphic * Graphic::sInstance = NULL;

Graphic * Graphic::GetInstance()
{
	if (sInstance == NULL)
	{
		sInstance = new Graphic();
	}

	return sInstance;
}

void Graphic::ReleaseInstance()
{
	delete sInstance;
	sInstance = NULL;
}

Graphic::Graphic()
{
	ZeroMemory(&d3dPP, sizeof(d3dPP));
	d3dDevice = NULL;
	direct3D9 = NULL;
}

Graphic::~Graphic()
{
	d3dDevice->Release();
	d3dDevice = NULL;

	sprite->Release();
	sprite = NULL;

	cursorTexture->Release();
	cursorTexture = NULL;

	hammerTexture->Release();
	hammerTexture = NULL;
}

void Graphic::CreateGraphic()
{
	direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = BUFFER_WIDTH;
	d3dPP.BackBufferHeight = BUFFER_HEIGHT;
	d3dPP.hDeviceWindow = GWindows::GetInstance()->g_hWnd;

	hr[0] = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GWindows::GetInstance()->g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);

	//cursor
	hr[1] = D3DXCreateSprite(Graphic::GetInstance()->d3dDevice, &sprite);
	hr[2] = D3DXCreateTextureFromFile(Graphic::GetInstance()->d3dDevice, "Resource/Cursor.png", &cursorTexture);
	hr[3] = D3DXCreateTextureFromFile(Graphic::GetInstance()->d3dDevice, "Resource/hammer.png", &hammerTexture);

	for (int i = 0; i < 4; i++)
	{
		if (FAILED(hr[i]))
		{
			PostQuitMessage(0);
		}
	}

	cursorRect.top = cursorRect.left = 0;
	cursorRect.bottom = cursorRect.right = 32;

	scaling.x = scaling.y = 1.5f;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, NULL);
}

void Graphic::GraphicLoopStart()
{
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 127, 0), 1.0f, 0);

	d3dDevice->BeginScene();
}

void Graphic::GraphicLoopEnd()
{
	DrawCursor();

	d3dDevice->EndScene();

	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void Graphic::DrawCursor()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->SetTransform(&mat);

	sprite->Draw(cursorTexture, &cursorRect,
		&D3DXVECTOR3(cursorRect.left, cursorRect.top, 0),
		&D3DXVECTOR3(GWindows::GetInstance()->mousePos.x / scaling.x, GWindows::GetInstance()->mousePos.y / scaling.y, 0),
		D3DCOLOR_XRGB(255, 255, 255));

	sprite->End();
}
