#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// タイトルシーン
/// 
/// タイトルを表示して、キーを押したらプレイシーンに移行する。
/// </summary>
class StageSelectScene : public SceneBase
{
public:
	StageSelectScene();
	~StageSelectScene();
	void Update() override;
	void Draw() override;
};
