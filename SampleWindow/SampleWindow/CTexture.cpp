#include "stdafx.h"

#include <d3d9.h>
#include <d3dx9.h>

#include "CTexture.h"

CTexture::CTexture(LPDIRECT3DDEVICE9 pD3DDevice)
{
	m_pD3DDevice = pD3DDevice;
}

CTexture::~CTexture()
{
	for (int i = 0; i < TEXTURE_POOL_SIZE; ++i)
		ReleaseTexture(i);
}

int CTexture::GetEmptySlot() const
{
	for (int i = 0; i < TEXTURE_POOL_SIZE; ++i)
		if (m_pTextures[i] == NULL)
			return i;
	return -1;
}

int CTexture::LoadTexture(const TCHAR* filename)
{
	int slotID = GetEmptySlot();
	
	if (slotID == -1)
		return -1;

	D3DXIMAGE_INFO imginfo;
	LPDIRECT3DTEXTURE9 pTexture;

	auto hr = D3DXCreateTextureFromFileEx(m_pD3DDevice, filename, 0, 0, 0, 0
										, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT
										, D3DX_FILTER_NONE, D3DX_DEFAULT
										, D3DCOLOR_XRGB(0, 0, 0), &imginfo, NULL, &pTexture);

	if (FAILED(hr))
		return -1;

	m_pTextures[slotID] = pTexture;

	return slotID;

}

void CTexture::ReleaseTexture(int slotID)
{
	if (m_pTextures[slotID] != NULL)
	{
		m_pTextures[slotID]->Release();
		m_pTextures[slotID] = NULL;
	}
}