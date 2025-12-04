#include "Player.h"
#include "Input.h"
#include "globals.h"

namespace
{
	int RightHPberLeft = 690;
	int RightHPberRight = 1180;



	float PlayerHPbar = 0;
	int PlayerMaxHP = 0;
	int PlayerATK = 0;
	float PlayerHPbarWidth = 0;
}

Player::Player()
	: csv_("data/Player.csv")
{
	PlayerHP = csv_.GetFloat(3, 1);
	PlayerMaxHP = csv_.GetFloat(3, 1);
	PlayerATK = csv_.GetInt(1, 2);
}

Player::~Player()
{
}

void Player::Update()
{
	
}

void Player::Draw()
{
	float rate = PlayerHP / PlayerMaxHP;

	PlayerHPbar += (RightHPberRight - RightHPberLeft) * (1.0f - rate);

	if (RightHPberRight < RightHPberLeft)
	{
		RightHPberRight = RightHPberLeft;
	}

	if (PlayerHP <= 0)
	{
		PlayerHP = 0;
	}
	PlayerHPbarWidth = PlayerHPbar;
	PlayerHPbar = 0;

	DrawBox(RightHPberLeft, HPberTop, RightHPberRight - PlayerHPbarWidth, HPberUnder, GetColor(0, 255, 0), TRUE);
	if (rate <= 0.2f)
	{
		DrawBox(RightHPberLeft, HPberTop, RightHPberRight - PlayerHPbarWidth, HPberUnder, GetColor(255, 0, 0), TRUE);

	}
	else if (rate <= 0.5f)
	{
		DrawBox(RightHPberLeft, HPberTop, RightHPberRight - PlayerHPbarWidth, HPberUnder, GetColor(255, 255, 0), TRUE);

	}
	DrawFormatString(800, 120, GetColor(255, 255, 255), "%3.0f / %d", PlayerHP, PlayerMaxHP);
}

float Player::GetHP() const
{
    return PlayerHP;
}

int Player::GetATK() const
{
	return PlayerATK;
}

void Player::SetHP(float hp)
{
	PlayerHP = hp;
}
