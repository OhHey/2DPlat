#pragma once
#include "DXUtil.h"
#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "ddsTexture.h"

using namespace DirectX::SimpleMath;

class IElement2D
{
public:
	virtual ~IElement2D() {}

	//GETTERS
	virtual const Vector2& GetPosition() const = 0;
//	virtual const Vector2& GetOrigin() const = 0;
	virtual const Vector2& GetScale() const = 0;
	virtual const Color& GetTint() const = 0;
	virtual const float& GetAlpha() const = 0;
	virtual const float& GetRotation() const = 0;
	virtual const bool& GetFacing() const = 0;

	//SETTERS
	virtual void SetPosition(const Vector2& position) = 0;
//	virtual void SetOrigin(const Vector2& origin) = 0;
	virtual void SetScale(const Vector2& scale) = 0;
	virtual void SetTint(const Color& color) = 0;
	virtual void SetAlpha(const float alpha) = 0;
	virtual void SetRotation(const float rotation) = 0;
	virtual void SetTexture(ddsTexture* texture) = 0;
	virtual void SetFacing(const bool facing) = 0;

	//RENDER FUNCTIONS
	virtual void Draw(DirectX::SpriteBatch* spriteBatch) = 0;

};