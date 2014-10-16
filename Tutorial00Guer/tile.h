#pragma once
#include "Sprite.h"

enum tiletype { PLAYER, GROUND, BACKGROUND };
class tile
{
public:
	int m_type;
	Sprite m_pSprite;
	bool m_collidable;
	char m_c;
	Vector2 m_WorldPosition;
	Vector4 m_Box;

	Vector4 m_CollResults;
	Vector4 m_PrevCollResults;

	tile(char c);
	tile(Vector2 position);
	~tile(void);
};

