#pragma once
#include "../Library/\\GameObject.h"


class Map
	: public GameObject
{
public:
	Map();
	~Map();
	void Update() override;
	void Draw() override;

	void CameraWheel();
	void MouseHit();

	int hModel;
	int hStart;
	int hGoal;
	int hSelect;
	int charcterModel;

	VECTOR playerPos;
	int playerNode = -1;
	int selectNode = -1;

	VECTOR cameraPos = VGet(0.0f, 150.0f, -10.0f);
	VECTOR cameraTarget = VGet(0.0f, 0.0f, 0.0f);
	
};