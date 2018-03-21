#pragma once
#define TEXTURE_POOL_SIZE 8
class CTexture
{
public :
	explicit CTexture(LPDIRECT3DDEVICE9 pD3DDevice);
	virtual ~CTexture();

	int LoadTexture(const TCHAR* filename);
	void ReleaseTexture(int slotID);

	LPDIRECT3DTEXTURE9 GetTexture(int slotID) const
	{
		if (slotID < TEXTURE_POOL_SIZE)
			return m_pTextures[slotID];
		return NULL;
	}

private:
	int GetEmptySlot() const;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	LPDIRECT3DTEXTURE9 m_pTextures[TEXTURE_POOL_SIZE];
};