#include "stdafx.h"

#include <dinput.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "CInput.h"


CInput::CInput(HWND hWnd, HINSTANCE hInstance)
{
	m_lpDInput = NULL;
	m_lpKeyboard = NULL;

	InitInput(hWnd, hInstance);
}


CInput::~CInput()
{
	Shutdown();
}

bool CInput::InitInput(HWND hWnd, HINSTANCE hInstance)
{
	auto hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&m_lpDInput, NULL);
	
	if (FAILED(hr))
		return false;

	hr = m_lpDInput->CreateDevice(GUID_SysKeyboard, &m_lpKeyboard, NULL);
	if (FAILED(hr))
		return false;

	hr = m_lpKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
		return false;

	hr = m_lpKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(hr))
		return false;

	hr = m_lpKeyboard->Acquire();
	if (FAILED(hr))
		return false;

	return true;
}

bool CInput::IsEscapePressed()
{
	if (m_keyboardstate[DIK_ESCAPE] & 0x80)
		return true;
	return false;
}

bool CInput::ReadKeyboard()
{
	auto hr = m_lpKeyboard->GetDeviceState(sizeof(m_keyboardstate), (LPVOID)&m_keyboardstate);
	
	if (FAILED(hr))
	{
		if (hr == DIERR_NOTACQUIRED || hr == DIERR_INPUTLOST)
			m_lpKeyboard->Acquire();
		else
			return false;
	}
	return true;
}

void CInput::Shutdown()
{
	if (m_lpKeyboard != NULL)
	{
		m_lpKeyboard->Unacquire();
		m_lpKeyboard->Release();
		m_lpKeyboard = NULL;
	}
	if (m_lpDInput != NULL)
	{
		m_lpDInput->Release();
		m_lpDInput = NULL;
	}
}
