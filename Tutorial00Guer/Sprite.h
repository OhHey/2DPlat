#pragma once
#include "IElement2D.h"
#include "DDSTextureLoader.h"


class Sprite : public IElement2D
{
public:
	Sprite(void);
	Sprite(const Vector2& position, ddsTexture* texture);
	~Sprite(void);

	//GETTERS
	virtual const Vector2& GetPosition() const;
//	virtual const Vector2& GetOrigin() const;
	virtual const Vector2& GetScale() const;
	virtual const Color& GetTint() const;
	virtual const float& GetAlpha() const;
	virtual const float& GetRotation() const;
	virtual const bool& GetFacing() const;

	//SETTERS
	virtual void SetTexture(ddsTexture* texture);
	virtual void SetPosition(const Vector2& position);
//	virtual void SetOrigin(const Vector2& origin);
	virtual void SetScale(const Vector2& scale);
	virtual void SetTint(const Color& color);
	virtual void SetAlpha(const float alpha);
	virtual void SetRotation(const float rotation);
	virtual void SetFacing(const bool facing);
		
	//RENDER
	virtual void Draw(DirectX::SpriteBatch* spriteBatch);

	Vector2 m_Position;

protected:
	
	ddsTexture* m_pddsTexture;

	Vector2 m_Scale;
	Color	m_Tint;
	float	m_Alpha;
	float	m_Rotation;
	bool	m_Facing;	//0 = left, 1 = right
};

