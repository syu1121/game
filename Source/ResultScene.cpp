#include "ResultScene.h"
#include <DxLib.h>

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Update()
{
	if (CheckHitKey(KEY_INPUT_S)) {
		SceneManager::ChangeScene("TITLE");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void ResultScene::Draw()
{
	DrawString(0, 0, "RESULT SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
}
