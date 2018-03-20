#pragma once
class CInput
{
public:
	explicit CInput(HWND hWnd,HINSTANCE hInstance);
	virtual ~CInput();

	bool InitInput(HWND hWnd, HINSTANCE hInstance);
	void Shutdown();

	bool IsEscapePressed();
	bool ReadKeyboard();

private:
	LPDIRECTINPUT8 m_lpDInput;
	LPDIRECTINPUTDEVICE8 m_lpKeyboard;
	unsigned char m_keyboardstate[256];
};

