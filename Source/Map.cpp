#include "Map.h"
#include "globals.h"
#include "Input.h"
#include <assert.h>

Map::Map()
{
	hModel = MV1LoadModel("data/Map.mv1");
	
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
	
	SetLightDirection(VGet(0.0f, -1.0f, 1.0f));
	MV1SetPosition(hModel, VGet(0.0f, 0.0f, 0.0f));

	if (Input::IsKeyDown(KEY_INPUT_P))
	{
		SceneManager::ChangeScene("PLAY");
	}
}

void Map::Draw()
{
	//SetCameraPositionAndTarget_UpVecY(
	//	VGet(0.0f, 10.0f, 0.0f), // カメラ位置
	//	VGet(0.0f, 0.0f, 0.0f));      // 注視点
	MV1DrawModel(hModel);
	

	/*int x = 200;
	int y = 100;
	int size = 150;
	int space = 20;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int px = x + i * (size + space);
			int py = y + j * (size + space);
			DrawBox(x + i * (100 + 20), y + j * (100 + 20), x + i * (100 + 20) + 100, y + j * (100 + 20) + 100, GetColor(255, 255, 255), TRUE);
			if (i == 0 && j == 0)
			{
				DrawBox(x + i * (100 + 20), y + j * (100 + 20), x + i * (100 + 20) + 100, y + j * (100 + 20) + 100, GetColor(0, 255, 0), TRUE);
			}

			if (i == 3 && j == 3)
			{
				DrawBox(x + i * (100 + 20), y + j * (100 + 20), x + i * (100 + 20) + 100, y + j * (100 + 20) + 100, GetColor(255, 0, 0), TRUE);
			}


			if (mousePos.x >= px && mousePos.x <= px + size &&
				mousePos.y >= py && mousePos.y <= py + size)
			{
				
				if (Input::IsButtonDown(MOUSE_INPUT_LEFT))
				{
					DrawBox(x + i * (100 + 20), y + j * (100 + 20), x + i * (100 + 20) + 100, y + j * (100 + 20) + 100, GetColor(255, 255, 255), TRUE);
					SceneManager::ChangeScene("PLAY");
				}
			}
				

			
		}
	}



	

	

		*/
}
