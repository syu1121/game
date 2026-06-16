#include "Map.h"
#include "globals.h"
#include "Input.h"
#include <assert.h>
#include <vector>
#include "CsvReader.h"

struct Node
{
	int id;
	float x;
	float z;
	int link[6];
};
std::vector<Node> nodes;


Map::Map()
{
	hModel = MV1LoadModel("data/Map.mv1");
	charcterModel = MV1LoadModel("data/character.mv1");
	//hImage = LoadGraph("data/siro.pmg");
	SetBackgroundColor(100, 150, 255);
	MV1SetScale(hModel, VGet(50.0f, 50.0f, 50.0f));
	MV1SetScale(charcterModel, VGet(1.0f, 1.0f, 1.0f));
	
	CsvReader csv("data/Map.csv");
	for (int line = 1; line < csv.GetLines(); line++)
	{
		Node node;
		node.id = csv.GetInt(line, 0);
		node.x = csv.GetInt(line, 1);
		node.z = csv.GetInt(line, 2);

		for (int i = 0; i < 6; i++)
		{
			node.link[i] = csv.GetInt(line, i + 3);
		}

		nodes.push_back(node);
	}
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

	VECTOR pos = MV1GetPosition(hModel);

	float speed = 1.0f;

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

	//int wheel = GetMouseWheelRotVol();

	//cameraPos.y += wheel * 0.1f;

	int wheel = GetMouseWheelRotVol();
	VECTOR dir = VGet(0.0f, 0.0f, 0.0f);

	dir.x = cameraPos.x - cameraTarget.x;
	dir.y = cameraPos.y - cameraTarget.y;
	dir.z = cameraPos.z - cameraTarget.z;

	float len = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);

	dir.x /= len;
	dir.y /= len;
	dir.z /= len;

	float zoomSpeed = 10.0f;

	len -= wheel * zoomSpeed;

	cameraPos.x = cameraTarget.x + dir.x * len;
	cameraPos.y = cameraTarget.y + dir.y * len;
	cameraPos.z = cameraTarget.z + dir.z * len;

	SetCameraPositionAndTarget_UpVecY(cameraPos, cameraTarget);
	/*if (Input::IsKeyDown(KEY_INPUT_P))
	{
		SceneManager::ChangeScene("PLAY");
	}*/
	DrawFormatString(0, 0, GetColor(0, 0, 0), "camera: %.1f %.1f %.1f", cameraPos.x, cameraPos.y, cameraPos.z);
	DrawFormatString(20, 20, GetColor(0, 0, 0), "model: %.1f %.1f %.1f", pos.x, pos.y, pos.z);

	
	
	

}

void Map::Draw()
{
	//DrawGraph(0, 0, hImage, TRUE);
	//MV1SetPosition(hModel,VGet(posX, 0.0f, posZ));

	/*MV1SetPosition(hModel, VGet(0.0f, 0.0f, 0.0f));
	MV1DrawModel(hModel);

	MV1SetPosition(hModel, VGet(0.0f, 0.0f, 85.0f));
	MV1DrawModel(hModel);

	MV1SetPosition(hModel, VGet(75.0f, 0.0f, 42.5f));
	MV1DrawModel(hModel);*/

	
	
	for (const auto& node : nodes)
	{
		
		MV1SetPosition(hModel, VGet(node.x, 0.0f, node.z));
		MV1DrawModel(hModel);

	}
	/*for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			float offsetX = 0.0f;

			if (i % 2 == 1)
			{
				offsetX = xSpace / 2;
			}

			float posZ = j * xSpace + offsetX;
			float posX = i * zSpace;

			MV1SetPosition(hModel, VGet(posX, 0.0f, posZ));
			MV1DrawModel(hModel);
		}
	}*/
}