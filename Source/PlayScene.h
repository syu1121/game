#pragma once
#include "../Library/SceneBase.h"
#include "Playarea.h"

class PlayScene : public SceneBase
{
	Playarea* playarea;

public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;
};
