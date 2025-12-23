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
	int MaxCard = 10;
	int cardspace = 150;

	int cardPosX = 350;
	int cardPosY = 600;
	int radius = 30;

	int maxTurn = 5;
	int turnCount = 0;

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
	player = new Player();
	srand((unsigned)time(NULL));
	GenerateCards();

	turn = PLAYER_TURN;
	usecard = false;
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
		

		float ehp = enemy->GetHP();
		float php = player->GetHP();

		if (turn == PLAYER_TURN)
		{
			DrawString(500, 500, "player", GetColor(255, 255, 255));

			if (dx * dx + dy * dy <= radius * radius)
			{
				if (Input::IsButtonDown(MOUSE_INPUT_LEFT))
				{
					
					
					ehp -= rand() % 200;
					enemy->SetHP(ehp);

					cards.erase(cards.begin() + i);

					usecard = true;
					if (usecard == true)
					{
						turn = ENEMY_TURN;
					}
					break;
				}
			}
		}
		else if (turn == ENEMY_TURN)
		{
			DrawString(500, 500, "enemy", GetColor(255, 255, 255));

			if (Input::IsKeepKeyDown(KEY_INPUT_A))
			{
				int cnt = 0;
				cnt++;
				if (cnt )
				php -= rand() % 150;
				player->SetHP(php);
				usecard = false;
				if (usecard == false)
				{
					turn = PLAYER_TURN;
				}
				turnCount++;
			}

			
			
		}

		if (php <= 0)
		{
			SceneManager::ChangeScene("RESULT");
		}
		if (ehp <= 0)
		{
			SceneManager::ChangeScene("RESULT");
		}
		int color = GetElementColor(cards[i]);

		DrawCircle(x, cardPosY, radius, color, TRUE);
	}

	if (cards.size() == 0)
	{
		GenerateCards();
	}
	
	

}

void Playarea::Draw()
{
	
	DrawBox(100, HPberTop, 590, HPberUnder, GetColor(0, 255, 0), FALSE);
	DrawCircle(640, 75, 50, GetColor(255, 255, 255), TRUE);
	DrawFormatString(638, 40, GetColor(0, 0, 255),"%d", turnCount);
	DrawFormatString(638, 50, GetColor(0, 0, 255), "--");
	DrawFormatString(638, 60, GetColor(0, 0, 255), "%d", maxTurn);
	DrawBox(690, HPberTop, 1180, HPberUnder, GetColor(0, 255, 0), FALSE);
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
		return GetColor(185, 196, 183);
	}
	return GetColor(255, 255, 255);
}
