#include "Enemy.h"
#include "Input.h"
#include "globals.h"

namespace
{
	int LeftHPberLeft = 100;
	
	int LeftHPberRight = 590;
	

	
	float EnemyHPbar = 0;
	int EnemyMaxHP = 0;
	float EnemyHPbarWidth = 0;
}


Enemy::Enemy()
	:csv_("data/Enemy.csv")
{
	EnemyHP = csv_.GetFloat(3, 1);
	EnemyMaxHP = csv_.GetFloat(3, 1);

}

Enemy::~Enemy()
{
}

void Enemy::Update()
{

	
}

void Enemy::Draw()
{
	float rate = EnemyHP / EnemyMaxHP;


	EnemyHPbar += (LeftHPberRight - LeftHPberLeft) * (1.0 - rate);

	if (LeftHPberLeft > LeftHPberRight)
	{
		LeftHPberLeft = LeftHPberRight;
	}

	if (EnemyHP <= 0)
	{
		EnemyHP = 0;
	}
	EnemyHPbarWidth = EnemyHPbar;
	EnemyHPbar = 0;

	DrawBox(LeftHPberLeft + EnemyHPbarWidth, HPberTop, LeftHPberRight, HPberUnder, GetColor(0, 255, 0), TRUE);
	if (rate <= 0.2f)
	{
		DrawBox(LeftHPberLeft + EnemyHPbarWidth, HPberTop, LeftHPberRight, HPberUnder, GetColor(255, 0, 0), TRUE);
	}
	else if (rate <= 0.5f)
	{
		DrawBox(LeftHPberLeft + EnemyHPbarWidth, HPberTop, LeftHPberRight, HPberUnder, GetColor(255, 255, 0), TRUE);
	}

	
	DrawFormatString(500, 120, GetColor(255, 255, 255), "%3.0f / %d", EnemyHP, EnemyMaxHP);
}

float Enemy::GetHP() const
{
	return EnemyHP;
}

void Enemy::SetHP(float hp)
{
	EnemyHP = hp;
}
