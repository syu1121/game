#pragma once
#include "../Library/\\GameObject.h"

class Playarea
	: public GameObject
{
public:
	Playarea();
	~Playarea();
	void Update() override;
	void Draw() override;

};
