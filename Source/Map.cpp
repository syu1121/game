#include "Map.h"
#include "globals.h"
#include "Input.h"
#include <assert.h>

Map::Map()
{
	hModel = MV1LoadModel("data/Map.mv1");
	//hImage = LoadGraph("data/siro.pmg");
	SetBackgroundColor(255, 255, 255);
}

Map::~Map()
{
}

void Map::Update()
{

	Point mousePos;
	if (GetMousePoint(&mousePos.x, &mousePos.y) == -1)
	{
		return;
	}

	//MV1GetFrameLocalMatrix(hModel, 0);

	VECTOR pos = MV1GetFramePosition(hModel, 0);
	MV1SetScale(hModel, VGet(50.0f, 50.0f, 50.0f));


	SetLightDirection(VGet(0.0f, -1.0f, 1.0f));
	MV1SetPosition(hModel, VGet(0.0f, 0.0f, 0.0f));

	SetCameraPositionAndTarget_UpVecY(cameraPos, cameraTarget);

	float speed = 5.0f;

	if (Input::IsKeepKeyDown(KEY_INPUT_W))
	{
		cameraPos.z += speed;
		cameraTarget.z += speed;
	}

	if (Input::IsKeepKeyDown(KEY_INPUT_S))
	{
		cameraPos.z -= speed;
		cameraTarget.z -= speed;
	}


	if (Input::IsKeepKeyDown(KEY_INPUT_A))
	{
		cameraPos.x -= speed;
		cameraTarget.x -= speed;
	}

	if (Input::IsKeepKeyDown(KEY_INPUT_D))
	{
		cameraPos.x += speed;
		cameraTarget.x += speed;
	}

	if (Input::IsKeyDown(KEY_INPUT_P))
	{
		SceneManager::ChangeScene("PLAY");
	}
}

void Map::Draw()
{
	//DrawGraph(0, 0, hImage, TRUE);

	MV1DrawModel(hModel);



}