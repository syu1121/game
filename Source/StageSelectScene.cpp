#include "StageSelectScene.h"
#include <DxLib.h>

StageSelectScene::StageSelectScene()
{
	map = new Map();

}

StageSelectScene::~StageSelectScene()
{
}

void StageSelectScene::Update()
{
	
	if (CheckHitKey(KEY_INPUT_ESCAPE)) 
	{
		SceneManager::Exit();
	}
}


void StageSelectScene::Draw()
{
	DrawString(0, 0, "STAGESELECT SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
}
