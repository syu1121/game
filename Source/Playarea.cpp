#include "Playarea.h"
#include "Screen.h"
#include "Input.h"
#include "globals.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>


using namespace std;

vector<int> cards;
vector<int> selectedcard;

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

	if (turn == PLAYER_TURN)
	{
		for (int i = 0; i < displaycard; i++)
		{
			int x = cardPosX + i * cardspace;

			int dx = mousePos.x - x;
			int dy = mousePos.y - cardPosY;

			if (dx * dx + dy * dy <= radius * radius)
			{
				if (Input::IsButtonDown(MOUSE_INPUT_LEFT))
				{
					if (selectedcard.size() < 2 && find(selectedcard.begin(),selectedcard.end(),i) == selectedcard.end())
					{
						selectedcard.push_back(i);
					}
				}
			}
		}
	}


	if (turn == PLAYER_TURN && selectedcard.size() == 2)
	{
		int p = cards[selectedcard[0]];
		int e = rand() % 4;

		playerElement = p;
		enemyElement = e;

		float eHP = enemy->GetHP();
		

		float rate = GetRate(p, e);
		float dmg = 100 * rate;



		enemy->SetHP(eHP - dmg);

		sort(selectedcard.begin(), selectedcard.end(), greater<int>());
		for (int idx : selectedcard)
		{
			cards.erase(cards.begin() + idx);
		}


		selectedcard.clear();
		turn = ENEMY_TURN;
	}

	if (turn == ENEMY_TURN)
	{
		float pHP = player->GetHP();
		player->SetHP(pHP - (rand() % 150));
		
		turn = PLAYER_TURN;
	}


	if (cards.size() == 0)
	{
		GenerateCards();
	}

	if (player->GetHP() <= 0 || enemy->GetHP() <= 0)
	{
		SceneManager::ChangeScene("RESULT");
	}


	/*for (int i = 0; i < displaycard; i++)
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
					if (selectedcard.size() < 2)
					{
						selectedcard.push_back(i);
					}	
				}
			}

			if (selectedcard.size() == 2)
			{

				int p = cards[selectedcard[0]];
				int e = rand() % 4;

				float rate = GetRate(p, e);

				int max = 5;
				int min = -5;

				ehp -= rand() % 200;
				enemy->SetHP(ehp);

				for (int j = 1; i >= 0; j--)
				{
					cards.erase(cards.begin() + selectedcard[j]);
				}
				selectedcard.clear();

				turn = ENEMY_TURN;

				break;
			}
		}
		else if (turn == ENEMY_TURN)
		{
			DrawString(500, 500, "enemy", GetColor(255, 255, 255));

			php -= rand() % 150;
			player->SetHP(php);
			
			turn = PLAYER_TURN;
			turnCount++;
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
	}*/
}

void Playarea::Draw()
{
	int displaycard = min(5, (int)cards.size());

	for (int i = 0; i < displaycard; i++)
	{
		int x = cardPosX + i * cardspace;
		int color = GetElementColor(cards[i]);

		// ‘I‘ð’†‚ÍˆÃ‚­
		for (int idx : selectedcard)
		{
			if (idx == i)
			{
				color = GetColor(100, 100, 100);
			}
		}

		DrawCircle(x, cardPosY, radius, color, TRUE);
	}

	DrawFormatString(50, 200, GetColor(255, 255, 255), "PLAYER  : %s", GetElementName(playerElement));
	DrawFormatString(50, 230, GetColor(255, 255, 255), "ENEMY   : %s", GetElementName(enemyElement));


	DrawBox(100, HPberTop, 590, HPberUnder, GetColor(0, 255, 0), FALSE);
	DrawCircle(640, 75, 50, GetColor(255, 255, 255), TRUE);
	/*DrawFormatString(638, 40, GetColor(0, 0, 255),"%d", turnCount);
	DrawFormatString(638, 50, GetColor(0, 0, 255), "--");
	DrawFormatString(638, 60, GetColor(0, 0, 255), "%d", maxTurn);*/
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

float Playarea::GetRate(int a, int b)
{

	if (a == none || b == none)
	{
		return 1.0f;
	}

	if (a == b)
	{
		return 1.0f;
	}

	if (a == fire && b == wood)
	{
		return 1.5f;
	}

	if (a == wood && b == water)
	{
		return 1.5f;
	}

	if (a == water && b == fire)
	{
		return 1.5f;
	}

	return 0.5f;
}

const char* Playarea::GetElementName(int element)
{
	switch (element)
	{
	case 0: 
		return "FIRE";
	case 1:
		return "WATER";
	case 2:
		return "WOOD";
	case 3:
		return "NONE";
	default:
		return "UNKNOWN";
	}
}
