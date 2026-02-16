#include "EnemyScene.h"
#include <DxLib.h>


EnemyScene::EnemyScene()
{
	
}

EnemyScene::~EnemyScene()
{
}

void EnemyScene::Update()
{

	
}

void EnemyScene::Draw()
{

	DrawString(0, 0, "ENEMY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}
