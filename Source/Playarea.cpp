#include "Playarea.h"
#include "Screen.h"
#include "Input.h"
#include "globals.h"

namespace
{
	int LeftHPberLeft = 100;
	float HPberTop = 62.5f;
	int LeftHPberRight = 590;
	int HPberDown = 87.5;

	int RightHPberLeft = 690;
	int RightHPberRight = 1180;
	
	float HP = 100;
	float HPber = 0;
	int MaxHP = 100;
	float HPswap = 0;
}


Playarea::Playarea()
{
	
}

Playarea::~Playarea()
{
}

void Playarea::Update()
{
	
	

	Point mousePos;
	if (GetMousePoint(&mousePos.x, &mousePos.y) == -1)
	{
		return;
	}
	

	if (Input::IsButtonDown(MOUSE_INPUT_LEFT))
	{
		
		HP -= 1;

		float remainingHP = HP / MaxHP;
		

		HPber += (LeftHPberRight - LeftHPberLeft) * ( 1.0 - remainingHP);
		
		if (LeftHPberLeft > LeftHPberRight)
		{
			LeftHPberLeft = LeftHPberRight;
		}

		HPswap = HPber;
		HPber = 0;
	}

	if (Input::IsButtonDown(MOUSE_INPUT_RIGHT))
	{

	}
}

void Playarea::Draw()
{
	
	DrawBox(LeftHPberLeft + HPswap, HPberTop, LeftHPberRight, HPberDown, GetColor(0, 255, 0), TRUE);
	DrawBox(RightHPberLeft, HPberTop, RightHPberRight, HPberDown, GetColor(0, 255, 0), TRUE);
	DrawFormatString(500, 120, GetColor(255, 255, 255), "%3.0f / %d", HP, MaxHP);

	DrawBox(100, HPberTop, 590, HPberDown, GetColor(0, 255, 0), FALSE);
	DrawCircle(640, 75, 50, GetColor(255, 255, 255), TRUE);
	DrawBox(690, HPberTop, 1180, HPberDown, GetColor(0, 255, 0), FALSE);
}
