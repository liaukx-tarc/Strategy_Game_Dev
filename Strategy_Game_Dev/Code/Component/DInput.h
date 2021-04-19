#ifndef D_INPUT
#define D_INPUT
#include <dinput.h>

class DInput
{
private:
	static DInput* sInstance;
	DInput();
	~DInput();

	HRESULT hr[3];

	LPDIRECTINPUTDEVICE8 dInputKeyboardDevice;
	LPDIRECTINPUTDEVICE8 dInputMouseDevice;
	
public:
	static DInput* GetInstance();
	static void ReleaseInstance();

	LPDIRECTINPUT8 dInput;
	DIMOUSESTATE mouseState;
	
	BYTE  diKeys[256];

	void CreateInput();
	void InputLoop();
};

#endif // !DIRECT_INPUT
