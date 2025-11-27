#pragma once
#include "../Library/\\GameObject.h"
#include "Enemy.h"

class Playarea
	: public GameObject
{
	Enemy* enemy;
public:
	Playarea();
	~Playarea();
	void Update() override;
	void Draw() override;

	void GenerateCards();
	int GetElementColor(int element);
};
