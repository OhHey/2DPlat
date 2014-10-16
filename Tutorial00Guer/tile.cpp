#include "tile.h"


tile::tile(char c)
{
	m_c = c;
	if (c == 'X')
	{
		m_collidable = 1;
		m_type = GROUND;
	}

	if (c == 'G')
	{
		m_collidable = 1;
		m_type = GROUND;
	}
		
	if (c == 'O')
	{
		m_collidable = 0;
		m_type = BACKGROUND;
	}

	m_PrevCollResults = Vector4(0,0,0,0);
	m_CollResults = Vector4(0,0,0,0);

}

tile::tile(Vector2 position)
{
	m_WorldPosition = position;
	m_type = PLAYER;
	m_PrevCollResults = Vector4(0,0,0,0);
	m_CollResults = Vector4(0,0,0,0);
}

tile::~tile(void)
{
	//if(m_pSprite != nullptr)
	//	Memory::SafeDelete(m_pSprite);
}
