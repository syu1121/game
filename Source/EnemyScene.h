#pragma once
#include "../Library/SceneBase.h"
#include "Playarea.h"

class EnemyScene : public SceneBase
{
	Playarea* playarea;

public:
	EnemyScene();
	~EnemyScene();
	void Update() override;
	void Draw() override;
};
