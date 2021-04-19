#include "DInput.h"
#include "G_Windows.h"

#include <stdio.h>

//singleton
DInput* DInput::sInstance = NULL;

DInput* DInput::GetInstance()
{
	if (DInput::sInstance == NULL)
	{
		sInstance = new DInput;
	}

	return sInstance;
}

void DInput::ReleaseInstance()
{
	delete sInstance;
	sInstance = NULL;
}

DInput::DInput()
{
	dInput = NULL;

	ZeroMemory(&diKeys, sizeof(diKeys));
	ZeroMemory(&mouseState, sizeof(mouseState));
}

DInput::~DInput()
{
	dInputKeyboardDevice->Unacquire();
	dInputKeyboardDevice->Release();
	dInputKeyboardDevice = NULL;

	dInputMouseDevice->Unacquire();
	dInputMouseDevice->Release();
	dInputMouseDevice = NULL;

	dInput->Release();
	dInput = NULL;
}

void DInput::CreateInput()
{
	hr[0] = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);

	//keyBoard
	hr[1] = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);
	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);

	//mouse
	hr[2] = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);
	dInputMouseDevice->SetDataFormat(&c_dfDIMouse);

	for (size_t i = 0; i < 3; i++)
	{
		if (FAILED(hr[i]))
		{
			PostQuitMessage(0);
		}
	}

	dInputKeyboardDevice->SetCooperativeLevel(GWindows::GetInstance()->g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	dInputMouseDevice->SetCooperativeLevel(GWindows::GetInstance()->g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
}

void DInput::InputLoop()
{
	hr[0] = dInputKeyboardDevice->GetDeviceState(256, diKeys);
	hr[1] = dInputMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouseState);

	if (FAILED(hr[0]))
	{
		dInputKeyboardDevice->Acquire();
	}

	if (FAILED(hr[1]))
	{
		dInputMouseDevice->Acquire();
	}
}