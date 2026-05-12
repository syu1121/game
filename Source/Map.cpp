#include "Map.h"
#include "globals.h"
#include "Input.h"
#include <assert.h>

Map::Map()
{
	hModel = MV1LoadModel("data/Map.mv1");
	charcterModel = MV1LoadModel("data/character.mv1");
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
	MV1SetScale(charcterModel, VGet(30.0f, 30.0f, 30.0f));

	SetLightDirection(VGet(0.0f, -1.0f, 1.0f));

	/*MV1SetPosition(charcterModel, VGet(-75.0f, 0.0f, 0.0f));
	MV1DrawModel(charcterModel);*/

	MV1SetPosition(hModel, VGet(0.0f, 0.0f, 0.0f));
	MV1DrawModel(hModel);

	MV1SetPosition(hModel, VGet(0.0f, 0.0f, 85.0f));
	MV1DrawModel(hModel);

	MV1SetPosition(hModel, VGet(75.0f, 0.0f, 42.5f));
	MV1DrawModel(hModel);

	SetCameraPositionAndTarget_UpVecY(cameraPos, cameraTarget);

	float speed = 5.0f;

	if (Input::IsKeepKeyDown(KEY_INPUT_W))
	{
		cameraPos.z -= speed;
		cameraTarget.z -= speed;
	}

	if (Input::IsKeepKeyDown(KEY_INPUT_S))
	{
		cameraPos.z += speed;
		cameraTarget.z += speed;
	}


	if (Input::IsKeepKeyDown(KEY_INPUT_A))
	{
		cameraPos.x += speed;
		cameraTarget.x += speed;
	}

	if (Input::IsKeepKeyDown(KEY_INPUT_D))
	{
		cameraPos.x -= speed;
		cameraTarget.x -= speed;
	}

	if (Input::IsKeyDown(KEY_INPUT_P))
	{
		SceneManager::ChangeScene("PLAY");
	}
}

void Map::Draw()
{
	//DrawGraph(0, 0, hImage, TRUE);

	
	
	//MV1SetPosition(hModel,VGet(posX, 0.0f, posZ));
	float a = 85.0f;

	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{

		}
	}
	

}