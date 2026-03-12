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

	

};
