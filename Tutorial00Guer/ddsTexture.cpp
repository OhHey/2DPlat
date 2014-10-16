#include "ddsTexture.h"


ddsTexture::ddsTexture(ID3D11Device* device, const wchar_t* file)
{
	HR(DirectX::CreateDDSTextureFromFile(device, file, &m_pResource, &m_pTexture));
	Utility::GetTextureDim(m_pResource, &m_Width, &m_Height);
	m_Origin = Vector2(0, 0);
	m_SourceRect.left = 0;
	m_SourceRect.top = 0;
	m_SourceRect.bottom = m_Height;
	m_SourceRect.right = m_Width;
}


ddsTexture::~ddsTexture(void)
{
	Memory::SafeRelease(m_pTexture);
	Memory::SafeRelease(m_pResource);
}
