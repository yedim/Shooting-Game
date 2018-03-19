#include "stdafx.h"

#include <time.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "CScreen.h"


CScreen::CScreen(HWND hWnd)
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;

	InitScreen(hWnd);
}


CScreen::~CScreen()
{
	ShutdownScreen();
}

bool CScreen::InitScreen(HWND hWnd)
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);	//Direct3D 객체를 생성

	if (m_pD3D == NULL)
		return false;
	
	RECT rc;
	GetClientRect(hWnd, &rc);					//Client가 가지고 있는 Rect 가져오기

	int width = rc.right - rc.left + 1;
	int height = rc.bottom - rc.top + 1;

	
	D3DPRESENT_PARAMETERS d3dpp;				//디바이스 생성 위한 구조체
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;//윈도우 모드
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;	//바탕화면 모드 맞춰서 후면버퍼 생성
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.hDeviceWindow = hWnd;

	auto hr = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd
								, D3DCREATE_HARDWARE_VERTEXPROCESSING, 
									&d3dpp, &m_pD3DDevice);//시연인자,생성된 장치
	
	if (FAILED(hr))
		return false;

	return true;

}

void CScreen::ShutdownScreen()
{
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

void CScreen::BeginRender()
{
	if (m_pD3DDevice == NULL)
		return;

	m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

}
void CScreen::EndRender()
{
	m_pD3DDevice->Present(0, 0, 0, 0);
}