#include "Playarea.h"
#include "Screen.h"
#include "Input.h"
#include "globals.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

vector<int> cards;
vector<int> enemycards;

vector<int> selectedcard;
vector<int> enemyselected;

vector<std::string> battleLog;


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

	turn = ENEMY_TURN;
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

	if (mousePos.x > 50 && mousePos.x < 100 && mousePos.y > 300 && mousePos.y < 400 && Input::IsButtonDown(MOUSE_INPUT_LEFT))
	{
		SceneManager::ChangeScene("ENEMY SCENE");
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
		
		
		
		turn = BATTLE_PHASE;
	}

	if (turn == ENEMY_TURN)
	{
		EnemySelectCards();
		
		turn = PLAYER_TURN;
	}

	if (turn == BATTLE_PHASE)
	{
		int p1 = cards[selectedcard[0]];
		int p2 = cards[selectedcard[1]];

		int e1 = enemycards[enemyselected[0]];
		int e2 = enemycards[enemyselected[1]];

		float dmg1 = 200 * GetRate(p1, e1);
		float dmg2 = 200 * GetRate(p2, e2);

		int enemyHP = enemy->GetHP();
		enemy->SetHP(enemyHP - (dmg1 + dmg2));

		float enemydmg1 = 200 * GetRate(e1, p1);
		float enemydmg2 = 200 * GetRate(e2, p2);

		int playerHP = player->GetHP();
		player->SetHP(playerHP - (enemydmg1 + enemydmg2));


		string log = string("Player: ") + GetElementName(p1) + " vs Enemy: " + GetElementName(e1) + " -> " + to_string((int)dmg1) + " damage";
		string log2 = string("Player: ") +GetElementName(p2) + " vs Enemy: " + GetElementName(e2) + " -> " + to_string((int)dmg2) + " damage";

		battleLog.push_back(log);
		battleLog.push_back(log2);
		



		sort(selectedcard.begin(), selectedcard.end(), greater<int>());
		for (int idx : selectedcard)
		{
			cards.erase(cards.begin() + idx);
		}

		sort(enemyselected.begin(), enemyselected.end(), greater<int>());
		for (int idx : enemyselected)
		{
			enemycards.erase(enemycards.begin() + idx);
		}

		selectedcard.clear();
		enemyselected.clear();

		turn = ENEMY_TURN;
	}


	if (cards.size() == 0)
	{
		GenerateCards();
	}

	if (player->GetHP() <= 0 || enemy->GetHP() <= 0)
	{
		SceneManager::ChangeScene("RESULT");
	}


	
}

void Playarea::Draw()
{
	int displaycard = min(5, (int)cards.size());
	int disenemycard = min(5, (int)enemycards.size());


	int startX = 50;
	int endX = 150;
	int y = 300;
	int boxSize = 15;   // ” ‚Ì‘å‚«‚³

	float interval = (endX - startX) / 5.0f;

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

	DrawBox(50, 300, 150, 500, GetColor(255, 255, 255), FALSE);


	for (int i = 0; i < disenemycard; i++)
	{
		int color = GetElementColor(enemycards[i]);
		int x = startX + interval * i;
		DrawBox(x, 480, x + boxSize, 500, color, TRUE);
		
	}

	if (!enemyselected.empty())
	{
		int element = enemycards[enemyselected[0]];
		int color = GetElementColor(element);

		DrawCircle(100, 350, 20, color, TRUE);
	}

	for (int i = 0; i < battleLog.size(); i++)
	{
		DrawString(50, 550 + i * 20, battleLog[i].c_str(), GetColor(255, 255, 255));
	}

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
	enemycards.clear();


	for (const auto& type : cardTypes)
	{
		for (int i = 0; i < type.count; i++)
		{
			cards.push_back(type.element);
			enemycards.push_back(type.element);
		}
	}

	for (int i = 0; i < cards.size(); i++)
	{
		int r = rand() % cards.size();
		swap(cards[i], cards[r]);
		swap(enemycards[i], enemycards[r]);
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

float Playarea::GetRate(int p, int e)
{

	if (p == none || e == none)
	{
		return 1.0f;
	}

	if (p == e)
	{
		return 1.0f;
	}

	if (p == fire && e == wood)
	{
		return 1.5f;
	}

	if (p == wood && e == water)
	{
		return 1.5f;
	}

	if (p == water && e == fire)
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

void Playarea::EnemySelectCards()
{
	enemyselected.clear();

	while (enemyselected.size() < 2)
	{
		int i = rand() % enemycards.size();

		if (find(enemyselected.begin(), enemyselected.end(), i) == enemyselected.end())
		{
			enemyselected.push_back(i);
		}
	}
}
