#pragma once
#include "../Library/\\GameObject.h"
#include "CsvReader.h"

class Player
	: public GameObject
{

	CsvReader csv_;

	float PlayerHP;
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;

	float GetHP() const;
	int GetATK() const;
	void SetHP(float hp);




};