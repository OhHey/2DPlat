#pragma once
#include "Sprite.h"
#include "SimpleMath.h"
#include "tile.h"
#include <vector>

using namespace std;

enum PlayerStates { GROUNDED, STANDING, WALKING, RUNNING, FALLING };


class player
{
public:

	Vector2 m_WorldPosition;
	Vector2 m_RenderPosition;
	Vector2 m_Position;
	Vector2 m_Velocity;
	Vector2 m_Acceleration;
	int		m_State;
	int		m_PlayerHeight;
	int		m_PlayerWidth;
	Vector4 m_Colliding; //BLEFT = 1, BRIGHT = 2, BTOP = 3, BBOT = 4
	float	m_LastXColl, m_LastYColl;

	vector<vector<tile>> m_PlayerTiles;

	Sprite*		m_pSprite;
	
	bool initPlayer();
	player(Sprite* sprite);
	~player(void);
};

