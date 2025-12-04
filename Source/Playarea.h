#pragma once
#include "../Library/\\GameObject.h"
#include "Enemy.h"
#include "Player.h"

enum Turn
{
	PLAYER_TURN,
	ENEMY_TURN
};

class Playarea
	: public GameObject
{
	Enemy* enemy;
	Player* player;

	Turn turn;
	bool usecard;
public:
	Playarea();
	~Playarea();
	void Update() override;
	void Draw() override;

	void GenerateCards();
	int GetElementColor(int element);
};
