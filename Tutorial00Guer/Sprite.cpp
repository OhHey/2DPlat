#include "Sprite.h"


Sprite::Sprite(void)
{

}

Sprite::Sprite(const Vector2& position, ddsTexture* texture)
{
	m_Position = position;
	m_Alpha = 1.0f;
	m_Rotation = 0.0f;
	m_Scale = Vector2(1, 1);
	m_Tint = DirectX::Colors::White.v;
	m_pddsTexture = texture;
	m_Facing = 0;
}


Sprite::~Sprite(void)
{
	
}

const Vector2& Sprite::GetPosition() const
{
	return m_Position;
}

//const Vector2& Sprite::GetOrigin() const
//{
//	return m_Origin;
//}

const Vector2& Sprite::GetScale() const
{
	return m_Scale;
}

const Color& Sprite::GetTint() const
{
	return m_Tint;
}

const float& Sprite::GetAlpha() const
{
	return m_Alpha;
}

const float& Sprite::GetRotation() const
{
	return m_Rotation;
}

const bool& Sprite::GetFacing() const
{
	return m_Facing;
}

void Sprite::SetPosition(const Vector2& position)
{
	m_Position = position;
}

//void Sprite::SetOrigin(const Vector2& origin)
//{
//	m_Origin = origin;
//}

void Sprite::SetScale(const Vector2& scale)
{
	m_Scale = scale;
}

void Sprite::SetTint(const Color& color)
{
	m_Tint = color;
}

void Sprite::SetAlpha(const float alpha)
{
	m_Alpha = alpha;
}

void Sprite::SetRotation(const float rotation)
{
	m_Rotation = rotation;
}

void Sprite::SetFacing(const bool facing)
{
	m_Facing = facing;
}

void Sprite::Draw(DirectX::SpriteBatch* spriteBatch)
{
	if(!m_Facing)
		spriteBatch->Draw(m_pddsTexture->m_pTexture, m_Position, &m_pddsTexture->m_SourceRect, m_Tint, m_Rotation, m_pddsTexture->m_Origin, m_Scale, DirectX::SpriteEffects::SpriteEffects_None, 0.0f);
	else
		spriteBatch->Draw(m_pddsTexture->m_pTexture, m_Position, &m_pddsTexture->m_SourceRect, m_Tint, m_Rotation, m_pddsTexture->m_Origin, m_Scale, DirectX::SpriteEffects::SpriteEffects_FlipHorizontally, 0.0f);
}

void Sprite::SetTexture(ddsTexture* texture)
{
	m_pddsTexture = texture;
}
	