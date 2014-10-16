#pragma once
#include "SimpleMath.h"

enum COLLIDESIDE {BLEFT = 1, BRIGHT, BTOP, BBOT};

void AABBDistance(float Ax, float Ay, float AX, float AY, float Bx, float By, float BX, float BY)
{
	Vector2 Dmaj;
	Vector2 b2 = Vector2((BX - Bx) / 2, (BY - By) / 2);
	Vector2 a2 = Vector2((AX - Ax) / 2, (AY - Ay) / 2);
	Vector2 bcent = Vector2(b2.x + Bx, b2.y +By);
	Vector2 acent = Vector2(a2.x + Ax, a2.y +Ay);
	Vector2 D = bcent - acent;
	if(abs(D.x)>abs(D.y))
		Dmaj = Vector2(D.x/abs(D.x),0);
	else
		Dmaj = Vector2(0,D.y/abs(D.y));

	Vector2 NormalPosition = (acent + a2 + b2) * Dmaj;

	float d = sqrt(pow((bcent.x - NormalPosition.x),2) + pow((bcent - NormalPosition).y,22));

}

Vector4 AABBTest(float Ax, float Ay, float AX, float AY, float Bx, float By, float BX, float BY) //1 in results indicates axis is still seperated.
{
	Vector4 results(0,0,0,0);

	if(AX < Bx)
		results.x = 1;
	else
		results.x = 0;
	if(BX < Ax)
		results.y = 1;
	else
		results.y = 0;
	if(AY < By)
		results.z = 1;
	else
		results.z = 0;
	if(BY < Ay)
		results.w = 1;
	else
		results.w = 0;
	
	return results;
}

Vector4 AABBTestX(float Ax, float AX, float Bx, float BX)
{
	Vector4 results(0,0,0,0);

	if(AX < Bx)
		results.x = 1;
	else
		results.x = 0;
	if(BX < Ax)
		results.y = 1;
	else
		results.y = 0;
	
	return results;
}

Vector4 AABBTestY(float Ay, float AY, float By, float BY)
{
	Vector4 results(0,0,0,0);

	if(AY < By)
		results.z = 1;
	else
		results.z = 0;
	if(BY < Ay)
		results.w = 1;
	else
		results.w = 0;
	
	return results;
}

/*	Vector4 results(0,0,0,0);
	if (!(AX < Bx || BX < Ax || AY < By || BY < Ay)) 
	{
		if(AX > Bx && Ax < Bx)
			results.x = 1;
		if(BX > Ax && BX < AX)
			results.y = 1;
		if(AY > By && Ay < By)
			results.z = 1;
		if(BY > AY && Ay < BY)
			results.w = 1;
	}
	return results;
}*/