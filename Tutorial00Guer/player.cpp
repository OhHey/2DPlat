#include "player.h"


player::player(Sprite* sprite)
{
	m_pSprite = sprite;
	m_Velocity = Vector2(0,0);
	m_Acceleration = Vector2(0,0.0);
	m_RenderPosition = Vector2(400,300);
	m_WorldPosition = Vector2(400,200);
	m_State = FALLING;

	m_PlayerHeight = 4;
	m_PlayerWidth = 2;

	for (int i = 0; i < m_PlayerWidth; i++)
	{
		vector <tile> tempvector;
		m_PlayerTiles.push_back(tempvector);
		for (int j = 0; j < m_PlayerHeight; j++)
		{
			tile temptile(Vector2(m_WorldPosition.x+(i*31), m_WorldPosition.y+(j*31)));
			m_PlayerTiles[i].push_back(temptile);
			//m_PlayerTiles[i][j] = temptile;
				//(m_PlayerWidth/2) - 16 
		}
			//tile temptile(Vector2(m_WorldPosition.x - 16, (m_PlayerHeight/2));
			//m_Playertiles.push_back(temptile);
		
	}
}


player::~player(void)
{
	Memory::SafeDelete(m_pSprite);
}
