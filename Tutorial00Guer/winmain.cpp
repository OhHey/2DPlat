#include "DXApp.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "DDSTextureLoader.h"
#include "SimpleMath.h"
#include "Sprite.h"
#include "player.h"
#include "tile.h"
#include <vector>
#include <fstream>
#include "AABB.h"

using namespace std;

class TestApp : public DXApp
{
public:
	TestApp(HINSTANCE hInstance);
	~TestApp();

	bool Init() override;
	void Update(float dt) override;
	void Render(float dt) override;



	float CollisionTests();
	float CollisionTestsX(); //Returns adjustmest required to X axis
	float CollisionTestsY(); //Returns adjustmest required to Y axis
	void LoadLevel();
	void UpdateLevel();
	void UpdatePlayer();

private:


	std::unique_ptr<DirectX::SpriteBatch> spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> spriteFont;
	ddsTexture* aasteroid;
	ddsTexture* playertext;
	ddsTexture* playerwalking;
	ddsTexture* Xtext;
	ddsTexture* Otext;

	ddsTexture* backdropred1;
	ddsTexture* ground1greenbrown;
	ddsTexture* underground1greenbrown;


	Sprite* playersprite;
	player* thePlayer;

	vector< vector <tile> > room;
	int roomx, roomy, tilesize;
	bool updatex, updatey;

	Vector4 collisionResults;
	vector<Vector2> collidedTiles;

	//Delete below me
	bool temptoggle;
	

};

int WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd )
{
	TestApp tApp(hInstance);

	if(!tApp.Init()) return 1;

	return tApp.Run();
}

TestApp::TestApp( HINSTANCE hInstance ) : DXApp(hInstance)
{

}

TestApp::~TestApp()
{
	//Memory::SafeDelete(playersprite);
}

bool TestApp::Init()
{
	if(!DXApp::Init())
		return false;

	tilesize = 32;

	//CREATE SPRITEBATCH
	spriteBatch.reset(new DirectX::SpriteBatch(m_pImmediateContext));

	//CREATE SPRITEFONT OBJECT
	spriteFont.reset(new DirectX::SpriteFont(m_pDevice, L"Arial.spritefont"));

	aasteroid = new ddsTexture(m_pDevice, L"wtf.dds");
	playertext = new ddsTexture(m_pDevice, L"player.dds");
	playerwalking = new ddsTexture(m_pDevice, L"playerwalking.dds");
	Otext = new ddsTexture(m_pDevice, L"o.dds");
	Xtext = new ddsTexture(m_pDevice, L"x.dds");

	backdropred1 = new ddsTexture(m_pDevice, L"backdropred1.dds");
	underground1greenbrown = new ddsTexture(m_pDevice, L"underground1greenbrown.dds");
	ground1greenbrown = new ddsTexture(m_pDevice, L"ground1greenbrown.dds");

	playersprite = new Sprite(DirectX::SimpleMath::Vector2(100,100), aasteroid);
	thePlayer = new player(playersprite);

	LoadLevel();
	return true;
}

void TestApp::LoadLevel()
{
	room.clear();
	
	char c;

	fstream tilemap;
	tilemap.open("tilemap.txt");

	if(!tilemap.is_open())
		OutputDebugString("FAILED TO OPEN TILEMAP");

	tilemap>>roomx;
	tilemap>>roomy;

	for(int i = 0;i<roomy;i++)
	{
		vector <tile> tempvector;
		room.push_back(tempvector);

		for(int j = 0;j<roomx;j++)
		{
			tilemap>>c;
			tile temptile(c);
			
			room[i].push_back(temptile);
			if(c == 'X')
				room[i][j].m_pSprite = Sprite(Vector2(j*tilesize,i*tilesize),underground1greenbrown);
			else if(c == 'O')
				room[i][j].m_pSprite = Sprite(Vector2(j*tilesize,i*tilesize),backdropred1);
			else if(c == 'G')
				room[i][j].m_pSprite = Sprite(Vector2(j*tilesize,i*tilesize), ground1greenbrown);

			room[i][j].m_WorldPosition = Vector2(j*tilesize,i*tilesize);
		}
	}


	tilemap.close();
}



void TestApp::UpdatePlayer()
{
	updatex = true;
	updatey = true;

	if (thePlayer->m_WorldPosition.x < 400)
	{
		thePlayer->m_RenderPosition.x = thePlayer->m_WorldPosition.x;
		updatex = false;
	}

	if (thePlayer->m_WorldPosition.y < 300)
	{
		updatey = false;
		thePlayer->m_RenderPosition.y = thePlayer->m_WorldPosition.y;
	}

	if (((roomx * tilesize) - thePlayer->m_WorldPosition.x) < 400)
	{
		thePlayer->m_RenderPosition.x = 800 - ((roomx * tilesize) - thePlayer->m_WorldPosition.x);
		updatex = false;
	}

	if (((roomy * tilesize) - thePlayer->m_WorldPosition.y) < 300)
	{
		thePlayer->m_RenderPosition.y = 600 - ((roomy * tilesize) - thePlayer->m_WorldPosition.y);
		updatey = false;
	}
	//to vegas!
}

void TestApp::UpdateLevel()
{
	for(int i = 0;i<roomy;i++)
	{
		vector <tile> tempvector;
		room.push_back(tempvector);
		for(int j = 0;j<roomx;j++)
		{	
			if (updatex)
				room[i][j].m_pSprite.m_Position.x = (room[i][j].m_WorldPosition.x - thePlayer->m_WorldPosition.x + 400);
			if (updatey)
				room[i][j].m_pSprite.m_Position.y = (room[i][j].m_WorldPosition.y - thePlayer->m_WorldPosition.y + 300);
		}
	}
}

float TestApp::CollisionTestsX()
{
	collidedTiles.clear(); //CLEAR LIST OF COLLIDED TILES
	temptoggle = false; //FOR SHOWING COLLIDED TEXT
	for(int i = 0;i < roomy;i++) //LOOP THROUGH ALL TILES
	{
		for(int j = 0;j < roomx;j++)
		{
			if(room[i][j].m_collidable == true)
			{
				room[i][j].m_CollResults = AABBTest(thePlayer->m_WorldPosition.x, //TEST ALL TILES FOR COLLISION
					thePlayer->m_WorldPosition.y, 
					thePlayer->m_WorldPosition.x + (thePlayer->m_PlayerWidth*31),
					thePlayer->m_WorldPosition.y + (thePlayer->m_PlayerHeight*31),
					room[i][j].m_WorldPosition.x,
					room[i][j].m_WorldPosition.y,
					room[i][j].m_WorldPosition.x + tilesize,
					room[i][j].m_WorldPosition.y + tilesize);

				if((room[i][j].m_CollResults.x + room[i][j].m_CollResults.y + room[i][j].m_CollResults.z + room[i][j].m_CollResults.w) == 0) //IF COLLIDING
				{
					collidedTiles.push_back(Vector2(i,j)); //ADD TO LIST OF TILES COLLIDING
					temptoggle = true;
				}

				else
					room[i][j].m_PrevCollResults = room[i][j].m_CollResults; //IF NOT COLLIDING WE WONT TOUCH THIS AGAIN, SAVE AND MOVE ON
			}
		}
	}

	for(int i = 0;i < collidedTiles.size();i++) //CHECK TILES THAT FOR SURE HAD A COLLISION FOR X COLLISION, COMPARE SEPARATING AXIS FROM LAST FRAME
	{
		if(room[collidedTiles[i].x][collidedTiles[i].y].m_CollResults.x != room[collidedTiles[i].x][collidedTiles[i].y].m_PrevCollResults.x) //I CHANGED
		{			
			return room[collidedTiles[i].x][collidedTiles[i].y].m_WorldPosition.x - (0.01 + thePlayer->m_WorldPosition.x + (thePlayer->m_PlayerWidth * 31)); //Bx - AX
		}
		if(room[collidedTiles[i].x][collidedTiles[i].y].m_CollResults.y != room[collidedTiles[i].x][collidedTiles[i].y].m_PrevCollResults.y) //I CHANGED
		{
			return (room[collidedTiles[i].x][collidedTiles[i].y].m_WorldPosition.x + tilesize) - thePlayer->m_WorldPosition.x + 0.01; //BX - Ax
		}
	}
	return 0;
}

float TestApp::CollisionTestsY() //REPEAT FOR Y COLLISIONS
{
	collidedTiles.clear();
	for(int i = 0;i < roomy;i++)
	{
		for(int j = 0;j < roomx;j++)
		{
			if(room[i][j].m_collidable == true)
			{
				room[i][j].m_CollResults = AABBTest(thePlayer->m_WorldPosition.x,
					thePlayer->m_WorldPosition.y, 
					thePlayer->m_WorldPosition.x + (thePlayer->m_PlayerWidth*31),
					thePlayer->m_WorldPosition.y + (thePlayer->m_PlayerHeight*31),
					room[i][j].m_WorldPosition.x,
					room[i][j].m_WorldPosition.y,
					room[i][j].m_WorldPosition.x + tilesize,
					room[i][j].m_WorldPosition.y + tilesize);

				if((room[i][j].m_CollResults.x + room[i][j].m_CollResults.y + room[i][j].m_CollResults.z + room[i][j].m_CollResults.w) == 0) //IF COLLIDING
				{
					collidedTiles.push_back(Vector2(i,j));
					temptoggle = true;
				}

				else
					room[i][j].m_PrevCollResults = room[i][j].m_CollResults; //IF NOT COLLIDING WE WONT TOUCH THIS AGAIN, SAVE AND MOVE ON
			}
		}
	}

	for(int i = 0;i < collidedTiles.size();i++) //CHECK TILES THAT FOR SURE HAD A COLLISION FOR Y COLLISION
	{
		if(room[collidedTiles[i].x][collidedTiles[i].y].m_CollResults.z != room[collidedTiles[i].x][collidedTiles[i].y].m_PrevCollResults.z) //I CHANGED
		{			
			return room[collidedTiles[i].x][collidedTiles[i].y].m_WorldPosition.y - (0.01 + thePlayer->m_WorldPosition.y + (thePlayer->m_PlayerHeight * 31)); //Bx - AX
		}
		if(room[collidedTiles[i].x][collidedTiles[i].y].m_CollResults.w != room[collidedTiles[i].x][collidedTiles[i].y].m_PrevCollResults.w) //I CHANGED
		{
			return (room[collidedTiles[i].x][collidedTiles[i].y].m_WorldPosition.y + tilesize) - thePlayer->m_WorldPosition.y; //BX - Ax
		}
	}
	return false;
}



void TestApp::Update( float dt)
{	
	thePlayer->m_Acceleration = Vector2(0.0,0.0);

	//APPLY ACCELERATION BASED ON INPUT AND ORIENT SPRITE
	if(theInput.IsWPressed()){
		thePlayer->m_Acceleration = thePlayer->m_Acceleration+Vector2(0.0,-1);
	}

	if(theInput.IsAPressed()){
		thePlayer->m_Acceleration = thePlayer->m_Acceleration+Vector2(-1,0.0);
		playersprite->SetFacing(0);
	}

	if(theInput.IsSPressed()){
		thePlayer->m_Acceleration = thePlayer->m_Acceleration+Vector2(0.0,1);
	}

	if(theInput.IsDPressed()){
		thePlayer->m_Acceleration = thePlayer->m_Acceleration+Vector2(1,0.0);
		playersprite->SetFacing(1);
	}

	if(theInput.IsSpacePressed() && thePlayer->m_State == GROUNDED)
	{
		thePlayer->m_Velocity.y = -300;
	}
	
	//UPDATE VELOCITY BASED ON ACCELERATION
	thePlayer->m_Velocity = thePlayer->m_Acceleration+thePlayer->m_Velocity;

	//CAP VELOCITY
	if(thePlayer->m_Velocity.x > 300)
		thePlayer->m_Velocity.x = 300;

	if(thePlayer->m_Velocity.x < -300)
		thePlayer->m_Velocity.x = -300;

	//SAVE TEMP VELOCITY VARS
	Vector2 TempPosition = thePlayer->m_WorldPosition;

	//DO X POSITION CHANGES FIRST
	thePlayer->m_WorldPosition.x = (thePlayer->m_WorldPosition.x+thePlayer->m_Velocity.x*dt);

	//TEST FOR COLLISIONS AFTER MOTION ALONG X
	float XChange = CollisionTestsX();
	if(XChange)
	{
		thePlayer->m_WorldPosition.x += CollisionTestsX();
		thePlayer->m_Velocity.x = 0;
	}

	//NOW DO Y MOTION
	thePlayer->m_WorldPosition.y = (thePlayer->m_WorldPosition.y+thePlayer->m_Velocity.y*dt);
	thePlayer->m_Velocity.y += 0.5; //APPLY GRAVITY

	//TEST FOR COLLISIONS AFTER MOTION ALONG Y
	float YChange = CollisionTestsY();
	if(YChange) //SINCE WE KNOW X MOTION CAUSED COLLISION TEST FOR LAST SEPARATING X AXIS
	{
		thePlayer->m_WorldPosition.y = TempPosition.y;
		thePlayer->m_Velocity.y = 0;
		if(YChange < 0)
			thePlayer->m_State = GROUNDED;
	}
	else
		thePlayer->m_State = FALLING;

	//CHECK PLAYER VS MAP EDGE
	UpdatePlayer();

	//IF NOT CLOSE TO MAP EDGE RENDER AT CENTER
	if (updatex & updatey)
	{
		thePlayer->m_RenderPosition = Vector2(400,300);
	}

	//SET SPRITE TO RENDER POSITION
	thePlayer->m_pSprite->SetPosition(thePlayer->m_RenderPosition);

	//APPLY PROPER PLAYER SPRITE TO STATUS
	if(thePlayer->m_State == WALKING)
		thePlayer->m_pSprite->SetTexture(playerwalking);
	else
		thePlayer->m_pSprite->SetTexture(playertext);

	UpdateLevel();

		
}

void TestApp::Render (float dt)
{
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, DirectX::Colors::CornflowerBlue);

	spriteBatch->Begin();

	//DRAW SPRITE
	

	int i,j;
	for(i = 0;i<roomy;i++)
	{
		for(j = 0;j<roomx;j++)
		{
			room[i][j].m_pSprite.Draw(spriteBatch.get());
		}
	}

	playersprite->Draw(spriteBatch.get());


	//DRAW FONT
	if(theInput.IsAPressed())
	spriteFont->DrawString(spriteBatch.get(), L"Hello World!", DirectX::SimpleMath::Vector2(600, 300));

	else
	spriteFont->DrawString(spriteBatch.get(), L"Hello World!", DirectX::SimpleMath::Vector2(64, 300));

	if(temptoggle)
		spriteFont->DrawString(spriteBatch.get(), L"COLLIDING", DirectX::SimpleMath::Vector2(300, 300));

	spriteBatch->End();

	HR(m_pSwapChain->Present(0, 0));
}






/*GENERAL METHODOLOGY
	Run CollisionTests() to find all tiles that the player tiles are intersecting. This is 
	done with AABB test, where each possible axis of separation returns a 1 or 0, 0 indicating
	no separation. If all axis return 0 into the results vector2, the tiles are colliding.
	The colliding tiles indicies are saved in the collidedTiles vector. At the start of each call
	of CollisionTests() clear this vector. 
	CollisionTestsX() and CollisionTestsY() are run for only the indicies know to be in collision,
	and determine if either of the separating axis for that axis has changed since the last frame.
	This frames results for CollisionTestsX() & Y are stored in collisionResults and compared to
	PrevCollResults. If there is a change, thePlayer->m_Colliding is updated to have a collision.

	Logic then happens based upon what is colliding to adjust the player appropriatly.
	

	//TEST FOR COLLISIONS - GETS ALL POSSIBLE COLLISIONS BSAED ON ALL MOTION
	CollisionTests();

	//if(thePlayer->m_State == GROUNDED) //IF LAST FRAME PLAYER COLLIDED WITH Y
	//{
		CollisionTestsY(); //CHECK IF STILL HITTING Y, IF SO CORRECT Y POSITION TO LAST FRAME
		if(thePlayer->m_Colliding.z || thePlayer->m_Colliding.w)
		{
			thePlayer->m_WorldPosition.y = TempPosition.y;
			thePlayer->m_Velocity.y = 0;
		}
		else
			thePlayer->m_State = FALLING;

		CollisionTests();

		CollisionTestsX(); //THEN TEST FOR X COLLISIONS TO AVOID BEING INSIDE A TILE ONLY DUE TO Y

		if(thePlayer->m_Colliding.x || thePlayer->m_Colliding.y)
		{
			thePlayer->m_WorldPosition.x = TempPosition.x;
			thePlayer->m_Velocity.x = 0;
		}

	/*}

	else//(thePlayer->m_State == FALLING) //IF PLAYER DID NOT COLLIDE IN Y LAST FRAME
	{
		CollisionTestsY();
		if(!(thePlayer->m_Colliding.z || thePlayer->m_Colliding.w)) //IF NOT HITTING ON Y, ADJUST X
		{
			CollisionTestsX();

			if(thePlayer->m_Colliding.x || thePlayer->m_Colliding.y)
			{
				thePlayer->m_WorldPosition.x = TempPosition.x;
				thePlayer->m_Velocity.x = 0;
			}
		}

		else
		{

			
				
			if(thePlayer->m_Colliding.z || thePlayer->m_Colliding.w) //IF FALLING AND HIT SOMETHING, GOTO GROUNDED STATE, ADJUST, CHECK X
			{
				thePlayer->m_WorldPosition.y = TempPosition.y;
				thePlayer->m_Velocity.y = 0;
				thePlayer->m_State = GROUNDED;
			}
	
			CollisionTestsX();
	
			if(thePlayer->m_Colliding.x || thePlayer->m_Colliding.y)
			{
				thePlayer->m_WorldPosition.x = TempPosition.x;
				thePlayer->m_Velocity.x = 0;
			}
		}

	}*/

	
	//ACT BASED UPON COLLISIONS - RESTORE PREV LOCATION AND SET AXIS VELOCITY TO ZERO
	/*
	if(thePlayer->m_Colliding.x || thePlayer->m_Colliding.y)
	{
		
		thePlayer->m_WorldPosition.x = TempPosition.x;
		thePlayer->m_Velocity.x = 0;
	}

	if(thePlayer->m_Colliding.z || thePlayer->m_Colliding.w)
	{
		thePlayer->m_State = GROUNDED;
		thePlayer->m_LastYColl = TempPosition.y;
		if(thePlayer->m_State != GROUNDED)
		{
			thePlayer->m_WorldPosition.y = TempPosition.y;
			thePlayer->m_Velocity.y = 0;
		}
	}
	
	void TestApp::CollisionTests()
{
	Vector4 results = Vector4(1,1,1,1); //1 MEANS TEST SHOWED NON COLLISION
	thePlayer->m_Colliding = Vector4(0,0,0,0); //SET TO PLAYER COLLIDING WITH NO TILES
	collisionResults = Vector4(0,0,0,0);
	collidedTiles.clear();
	temptoggle = false;
	for(int i = 0;i < roomy;i++)
		for(int j = 0;j < roomx;j++)
			if(room[i][j].m_collidable == true)
			{
				if(i == 7 && j == 10)
					int fake = 0;

				results = AABBTest(thePlayer->m_WorldPosition.x,
					thePlayer->m_WorldPosition.y, 
					thePlayer->m_WorldPosition.x + (thePlayer->m_PlayerWidth*32),
					thePlayer->m_WorldPosition.y + (thePlayer->m_PlayerHeight*32),
					room[i][j].m_WorldPosition.x,
					room[i][j].m_WorldPosition.y,
					room[i][j].m_WorldPosition.x + 32,
					room[i][j].m_WorldPosition.y + 32);

				if((results.x + results.y + results.z + results.w) == 0) //IF COLLIDING
				{
					collidedTiles.push_back(Vector2(i,j));
					temptoggle = true;
				}

				//else room[i][j].m_PrevCollResults = results; //TRACK FOR NEXT LOOP

			}
}

void TestApp::CollisionTestsX()
{
	
	for(int i = 0;i < collidedTiles.size();i++) //CHECK TILES THAT FOR SURE HAD A COLLISION FOR X COLLISION
		{

			collisionResults += AABBTestX(thePlayer->m_WorldPosition.x,
				thePlayer->m_WorldPosition.x + (thePlayer->m_PlayerWidth*32),
				room[collidedTiles[i].x][collidedTiles[i].y].m_WorldPosition.x,
				room[collidedTiles[i].x][collidedTiles[i].y].m_WorldPosition.x + 32);

			if(collisionResults.x != room[collidedTiles[i].x][collidedTiles[i].y].m_PrevCollResults.x) //I CHANGED
				thePlayer->m_Colliding.x = thePlayer->m_Colliding.x++;
			if(collisionResults.y != room[collidedTiles[i].x][collidedTiles[i].y].m_PrevCollResults.y) //I CHANGED
				thePlayer->m_Colliding.y = thePlayer->m_Colliding.y++;		
			
			room[collidedTiles[i].x][collidedTiles[i].y].m_PrevCollResults += collisionResults; //TRACK FOR NEXT LOOP
		}
}

void TestApp::CollisionTestsY()
{

	for(int i = 0;i < collidedTiles.size();i++) //CHECK TILES THAT FOR SURE HAD A COLLISION FOR Y COLLISION
		{

			collisionResults += AABBTestY(thePlayer->m_WorldPosition.y, 
				thePlayer->m_WorldPosition.y + (thePlayer->m_PlayerHeight*32),
				room[collidedTiles[i].x][collidedTiles[i].y].m_WorldPosition.y,
				room[collidedTiles[i].x][collidedTiles[i].y].m_WorldPosition.y + 32);

			if(collisionResults.z != room[collidedTiles[i].x][collidedTiles[i].y].m_PrevCollResults.z) //I CHANGED
				thePlayer->m_Colliding.z = thePlayer->m_Colliding.z++;
			if(collisionResults.w != room[collidedTiles[i].x][collidedTiles[i].y].m_PrevCollResults.w) //I CHANGED
				thePlayer->m_Colliding.w = thePlayer->m_Colliding.w++;

			room[collidedTiles[i].x][collidedTiles[i].y].m_PrevCollResults += collisionResults; //TRACK FOR NEXT LOOP
		}
}


//MORE FUCKED UP ATTEMPTS
float TestApp::CollisionTestsX()
{
	Vector4 results; //1 MEANS TEST SHOWED NON COLLISION
	for(int i = 0;i < collidedTiles.size();i++) //CHECK TILES THAT FOR SURE HAD A COLLISION FOR X COLLISION
		{

			results = AABBTestX(thePlayer->m_WorldPosition.x,
				thePlayer->m_WorldPosition.x + (thePlayer->m_PlayerWidth * 32),
				room[collidedTiles[i].x][collidedTiles[i].y].m_WorldPosition.x,
				room[collidedTiles[i].x][collidedTiles[i].y].m_WorldPosition.x + tilesize);

			if(results.x != room[collidedTiles[i].x][collidedTiles[i].y].m_PrevCollResults.x) //I CHANGED
			{			
				return room[collidedTiles[i].x][collidedTiles[i].y].m_WorldPosition.x - (0.01 + thePlayer->m_WorldPosition.x + (thePlayer->m_PlayerWidth * 32)); //Bx - AX
				return BLEFT;
			}

			if(results.y != room[collidedTiles[i].x][collidedTiles[i].y].m_PrevCollResults.y) //I CHANGED
			{
				return (room[collidedTiles[i].x][collidedTiles[i].y].m_WorldPosition.x + tilesize) - thePlayer->m_WorldPosition.x; //BX - Ax
				return BRIGHT;
			}
			
			//room[collidedTiles[i].x][collidedTiles[i].y].m_PrevCollResults += collisionResults; //TRACK FOR NEXT LOOP
			
		}
	return false;
}

float TestApp::CollisionTestsY()
{

	for(int i = 0;i < collidedTiles.size();i++) //CHECK TILES THAT FOR SURE HAD A COLLISION FOR Y COLLISION
		{

			collisionResults = AABBTestY(thePlayer->m_WorldPosition.y, 
				thePlayer->m_WorldPosition.y + (thePlayer->m_PlayerHeight * 32),
				room[collidedTiles[i].x][collidedTiles[i].y].m_WorldPosition.y,
				room[collidedTiles[i].x][collidedTiles[i].y].m_WorldPosition.y + tilesize);

			if(collisionResults.z != room[collidedTiles[i].x][collidedTiles[i].y].m_PrevCollResults.z) //I CHANGED
			{
				
				return BTOP;
			}

			if(collisionResults.w != room[collidedTiles[i].x][collidedTiles[i].y].m_PrevCollResults.w) //I CHANGED
			{
				
				return BBOT;
			}

			//room[collidedTiles[i].x][collidedTiles[i].y].m_PrevCollResults += collisionResults; //TRACK FOR NEXT LOOP
			
		}
	return false;
}
*/