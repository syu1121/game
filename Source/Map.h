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

	int hModel;
	int hImage;

	VECTOR cameraPos = VGet(0.0f, 150.0f, -10.0f);
	VECTOR cameraTarget = VGet(0.0f, 0.0f, 0.0f);

};