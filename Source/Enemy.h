#pragma once
#include "../Library/\\GameObject.h"
#include "CsvReader.h"

class Enemy
	: public GameObject
{

	CsvReader csv_;

	float EnemyHP;
public:
	Enemy();
	~Enemy();
	void Update() override;
	void Draw() override;

	float GetHP() const;
	void SetHP(float hp);

	

	
};
