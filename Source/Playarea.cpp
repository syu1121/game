#include "Playarea.h"
#include "Screen.h"
#include "Input.h"
#include "globals.h"
#include <cstdlib>
#include <ctime>
#include <vector>


using namespace std;

vector<int> cards;

struct CardType
{
	int element;
	int count;
};

namespace
{
	

	int RightHPberLeft = 690;
	int RightHPberRight = 1180;
	
	

	int MaxCard = 10;
	int cardspace = 150;

	int cardPosX = 350;
	int cardPosY = 600;
	int radius = 30;

	const int fire = 0;
	const int water = 1;
	const int wood = 2;
	const int none = 3;

	const CardType cardTypes[] = {
		{fire, 3},
		{water, 3},
		{wood, 3},
		{none, 1}
	};
}


Playarea::Playarea()
{
	enemy = new Enemy();
	srand((unsigned)time(NULL));
	GenerateCards();
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


	int displaycard = 5;
	if (cards.size() < displaycard)
	{
		displaycard = cards.size();
	}

	for (int i = 0; i < displaycard; i++)
	{
		int x = cardPosX + i * cardspace;

		int dx = mousePos.x - x;
		int dy = mousePos.y - cardPosY;

		if (dx * dx + dy * dy <= radius * radius)
		{
			if (Input::IsButtonDown(MOUSE_INPUT_LEFT))
			{
				float hp = enemy->GetHP();
				hp -= rand() % 200;
				enemy->SetHP(hp);
				
			}
			
		}

		int color = GetElementColor(cards[i]);

		DrawCircle(x, cardPosY, radius, color, TRUE);
	}
	
	if (Input::IsButtonDown(MOUSE_INPUT_RIGHT))
	{
		GenerateCards();
	}

	
}

void Playarea::Draw()
{
	DrawBox(RightHPberLeft, HPberTop, RightHPberRight, HPberDown, GetColor(0, 255, 0), TRUE);
	

	DrawBox(100, HPberTop, 590, HPberDown, GetColor(0, 255, 0), FALSE);
	DrawCircle(640, 75, 50, GetColor(255, 255, 255), TRUE);
	DrawBox(690, HPberTop, 1180, HPberDown, GetColor(0, 255, 0), FALSE);

	

	

	
}

void Playarea::GenerateCards()
{
	cards.clear();

	for (const auto& type : cardTypes)
	{
		for (int i = 0; i < type.count; i++)
		{
			cards.push_back(type.element);
		}
	}


	for (int i = 0; i < cards.size(); i++)
	{
		int r = rand() % cards.size();
		swap(cards[i], cards[r]);

	}
}

int Playarea::GetElementColor(int element)
{
	switch (element)
	{
	case 0:
		return GetColor(255, 0, 0);
	case 1:
		return GetColor(0, 0, 255);
	case 2:
		return GetColor(0, 255, 0);
	case 3:
		return GetColor(255, 255, 255);
	}
	return GetColor(255, 255, 255);
}
