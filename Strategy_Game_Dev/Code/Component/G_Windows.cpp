#include "G_Windows.h"
#include "Graphic.h"
#include "..\resource.h"

//Singleton
GWindows * GWindows::sInstance = NULL;

GWindows * GWindows::GetInstance()
{
	if (sInstance == NULL)
	{
		sInstance = new GWindows();
	}

	return sInstance;
}

void GWindows::ReleaseInstance()
{
	delete sInstance;
	sInstance = NULL;
}

GWindows::GWindows()
{
	g_hWnd = NULL;
	hInstance = GetModuleHandle(NULL);
	ZeroMemory(&wndClass, sizeof(wndClass));

	keyPress = 0;
	ZeroMemory(&mousePos, sizeof(mousePos));
}

GWindows::~GWindows()
{
	UnregisterClass(wndClass.lpszClassName, hInstance);
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		GWindows::GetInstance()->keyPress;
		break;

	case WM_MOUSEMOVE:
		GWindows::GetInstance()->mousePos.x = LOWORD(lParam) * BUFFER_WIDTH / WINDOWS_WIDTH;
		GWindows::GetInstance()->mousePos.y = HIWORD(lParam) * BUFFER_HEIGHT / WINDOWS_HEIGHT;

		if (GWindows::GetInstance()->mousePos.x < 0 || GWindows::GetInstance()->mousePos.x > BUFFER_WIDTH ||
			GWindows::GetInstance()->mousePos.y < 0 || GWindows::GetInstance()->mousePos.y > BUFFER_HEIGHT)
		{
			ShowCursor(true);
		}

		else
		{
			ShowCursor(false);
			GWindows::GetInstance()->mousePos.x = min(GWindows::GetInstance()->mousePos.x, BUFFER_WIDTH);
			GWindows::GetInstance()->mousePos.y = min(GWindows::GetInstance()->mousePos.y, BUFFER_HEIGHT);
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void GWindows::CreateWindows()
{
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WindowProcedure;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//App Name
	wndClass.lpszClassName = APP_NAME; //APP_NAME is a constant variable at define

	//App Cursor
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	//App Icon
	wndClass.hIcon = LoadIcon(hInstance, MAKEINTATOM(IDI_ICON1));

	RegisterClass(&wndClass);

	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, APP_NAME, WS_OVERLAPPEDWINDOW, 100, 50, WINDOWS_WIDTH + 17, WINDOWS_HEIGHT + 40, NULL, NULL, hInstance, NULL);
	ShowWindow(g_hWnd, 1);
}

bool GWindows::WindowsLoop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT) break;

		TranslateMessage(&msg);

		DispatchMessage(&msg);

	}

	return msg.message != WM_QUIT;
}