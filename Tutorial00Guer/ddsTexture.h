#pragma once

#include "DXUtil.h"
#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "DDSTextureLoader.h"

using namespace DirectX::SimpleMath;

class ddsTexture
{
public:

	ID3D11Resource*				m_pResource;
	ID3D11ShaderResourceView*	m_pTexture;
	UINT						m_Width;
	UINT						m_Height;
	RECT						m_SourceRect;
	Vector2 m_Origin;

	ddsTexture(ID3D11Device* device, const wchar_t* file);
	~ddsTexture(void);
};

