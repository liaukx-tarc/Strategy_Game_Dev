#ifndef G_WINDOWS
#define G_WINDOWS

#include <Windows.h>
#include <d3dx9.h>

#define WINDOWS_WIDTH	1280
#define WINDOWS_HEIGHT	720
#define APP_NAME		"Last Round"

class GWindows
{
private:
	static GWindows* sInstance;
	GWindows();
	~GWindows();

	WNDCLASS wndClass;
	HINSTANCE hInstance;

public:
	//Singleton
	static GWindows * GetInstance();
	static void ReleaseInstance();

	HWND g_hWnd;
	int keyPress;
	D3DXVECTOR2 mousePos;

	//Windows Function
	void CreateWindows();
	bool WindowsLoop();
};

#endif // !G_WINDOWS

