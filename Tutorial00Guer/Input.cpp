#include "Input.h"


Inputer::Inputer(void)
{
	checkInput();
}

void Inputer::checkInput()
{
	if(GetAsyncKeyState('W'))
		W = true;
	else
		W = false;

	if(GetAsyncKeyState('A'))
		A = true;
	else
		A = false;

	if(GetAsyncKeyState('S'))
		S = true;
	else
		S = false;

	if(GetAsyncKeyState('D'))
		D = true;
	else
		D = false;

	if(GetAsyncKeyState(VK_LSHIFT))
		LShift = true;
	else
		LShift = false;

	if(GetAsyncKeyState(VK_SPACE))
		Space = true;
	else
		Space = false;

}

bool Inputer::IsWPressed(){
	if (W)
		return true;
	else return false;
}

bool Inputer::IsAPressed(){
	if (A)
		return true;
	else return false;
}

bool Inputer::IsSPressed(){
	if (S)
		return true;
	else return false;
}

bool Inputer::IsDPressed(){
	if (D)
		return true;
	else return false;
}

bool Inputer::IsLShiftPressed(){
	if (LShift)
		return true;
	else return false;
}

bool Inputer::IsSpacePressed(){
	if (Space)
		return true;
	else return false;
}

Inputer::~Inputer(void)
{
}


