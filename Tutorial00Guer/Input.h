#pragma once

#include <Windows.h>

class Inputer
{
public:

	bool IsWPressed();
	bool IsAPressed();
	bool IsSPressed();
	bool IsDPressed();
	bool IsSpacePressed();
	bool IsLShiftPressed();
	void checkInput();

	Inputer(void);
	~Inputer(void);

private:
	bool W;
	bool A;
	bool S;
	bool D;
	bool LShift;
	bool Space;
};

