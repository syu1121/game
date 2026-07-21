#include "Map.h"
#include "globals.h"
#include "Input.h"
#include <assert.h>
#include <vector>
#include "CsvReader.h"

enum
{
	NORMAL = 0,
	START = 1,
	GOAL = 2
};

struct Node
{
	int id;
	float x;
	float z;
	int type;
	int link[6];
};
std::vector<Node> nodes;


Map::Map()
{
	hModel = MV1LoadModel("data/MAP/Map.mv1");
	hStart = MV1LoadModel("data/MAP/Start.mv1");
	hGoal = MV1LoadModel("data/MAP/Goal.mv1");
	hSelect = MV1LoadModel("data/MAP/Select.mv1");
	charcterModel = MV1LoadModel("data/character.mv1");
	
	SetBackgroundColor(100, 150, 255);
	MV1SetScale(hModel, VGet(50.0f, 50.0f, 50.0f));
	MV1SetScale(hStart, VGet(50.0f, 50.0f, 50.0f));
	MV1SetScale(hGoal, VGet(50.0f, 50.0f, 50.0f));
	MV1SetScale(hSelect, VGet(50.0, 50.0, 50.0));
	//MV1SetScale(charcterModel, VGet(1.0f, 1.0f, 1.0f));
	
	CsvReader csv("data/Map.csv");
	for (int line = 1; line < csv.GetLines(); line++)
	{
		Node node;
		node.id = csv.GetInt(line, 0);
		node.type = csv.GetInt(line, 1);
		node.x = csv.GetInt(line, 2);
		node.z = csv.GetInt(line, 3);
		
		for (int i = 0; i < 6; i++)
		{
			node.link[i] = csv.GetInt(line, i + 4);
		}

		nodes.push_back(node);
	}

	
}

Map::~Map()
{
}

void Map::Update()
{

	/*Point mousePos;
	if (GetMousePoint(&mousePos.x, &mousePos.y) == -1)
	{
		return;
	}*/
	SetLightDirection(VGet(0.0f, -1.0f, 1.0f));

	VECTOR pos = MV1GetPosition(hModel);

	float speed = 1.0f;
	float minX = 0.0f;
	float maxX = 400.0f;
	float minZ = 250.0f;
	float maxZ = 530.0f;

	if (Input::IsKeepKeyDown(KEY_INPUT_W))
	{
		cameraPos.z += speed;
		cameraTarget.z += speed;
		/*if (cameraTarget.z > maxZ)
		{
			cameraPos.z = maxZ;
			cameraTarget.z = maxZ - cameraTarget.z;
		}*/
	}

	if (Input::IsKeepKeyDown(KEY_INPUT_S))
	{
		cameraPos.z -= speed;
		cameraTarget.z -= speed;
		/*if (cameraTarget.z < minZ)
		{
			cameraPos.z = minZ;
			cameraTarget.z = minZ;
		}*/
	}

	if (Input::IsKeepKeyDown(KEY_INPUT_A))
	{
		cameraPos.x -= speed;
		cameraTarget.x -= speed;
		/*if (cameraTarget.x < minX)
		{
			cameraPos.x = minX;
			cameraTarget.x = minX;
		}*/
	}

	if (Input::IsKeepKeyDown(KEY_INPUT_D))
	{
		cameraPos.x += speed;
		cameraTarget.x += speed;
		/*if (cameraTarget.x > maxX)
		{
			cameraPos.x = maxX;
			cameraTarget.x = maxX;
		}*/
	}

	
	CameraWheel();
	
	MouseHit();


	DrawFormatString(0, 0, GetColor(0, 0, 0), "camera: %.1f %.1f %.1f", cameraPos.x, cameraPos.y, cameraPos.z);
	//DrawFormatString(20, 20, GetColor(0, 0, 0), "model: %.1f %.1f %.1f", pos.x, pos.y, pos.z);
}

void Map::Draw()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		bool isLink = false;
		const auto& node = nodes[i];

		if (selectNode != -1)
		{
			for (int j = 0; j < 6; j++)
			{
				DrawFormatString(0, 60 + j * 20, GetColor(255, 255, 255), "link[%d]=%d", j, nodes[selectNode].link[j]);
				if (nodes[selectNode].link[j] == node.id)
				{
					isLink = true;
					break;
				}
			}
		}
		

		switch (node.type)
		{
		case START:
			MV1SetPosition(hStart, VGet(node.x, 0.0f, node.z));
			MV1DrawModel(hStart);
			break;

		case GOAL:
			MV1SetPosition(hGoal, VGet(node.x, 0.0f, node.z));
			MV1DrawModel(hGoal);
			break;

		case NORMAL:
			MV1SetPosition(hModel, VGet(node.x, 0.0f, node.z));
			MV1DrawModel(hModel);
			break;
		}
		if (isLink)
		{
			MV1SetPosition(hSelect, VGet(node.x, 0.0f, node.z));
			MV1DrawModel(hSelect);
		}
		// 選択マスを表示
		if (i == selectNode)
		{
			DrawFormatString(node.x, node.z, GetColor(255, 0, 0), "OK");
			MV1SetPosition(hSelect, VGet(node.x, 0.0f, node.z));
			MV1DrawModel(hSelect);
			DrawFormatString(0, 40, GetColor(255, 255, 255), "selectNode = %d", selectNode);
		}
	}
}
void Map::CameraWheel()
{
	int wheel = GetMouseWheelRotVol();
	VECTOR dir = VGet(0.0f, 0.0f, 0.0f);

	float maxlen = 400.0f;
	float minlen = 150.0f;

	dir.x = cameraPos.x - cameraTarget.x;
	dir.y = cameraPos.y - cameraTarget.y;
	dir.z = cameraPos.z - cameraTarget.z;

	float len = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);

	

	dir.x /= len;
	dir.y /= len;
	dir.z /= len;

	float zoomSpeed = 10.0f;

	len -= wheel * zoomSpeed;

	

	if (len > maxlen)
	{
		len = maxlen;
	}

	if (len < minlen)
	{
		len = minlen;
	}

	cameraPos.x = cameraTarget.x + dir.x * len;
	cameraPos.y = cameraTarget.y + dir.y * len;
	cameraPos.z = cameraTarget.z + dir.z * len;

	SetCameraPositionAndTarget_UpVecY(cameraPos, cameraTarget);

	
}

void Map::MouseHit()
{
    Point mousePos;
    GetMousePoint(&mousePos.x, &mousePos.y);

    // レイの始点と終点
    VECTOR nearPos = ConvScreenPosToWorldPos(
        VGet((float)mousePos.x, (float)mousePos.y, 0.0f));

    VECTOR farPos = ConvScreenPosToWorldPos(
        VGet((float)mousePos.x, (float)mousePos.y, 1.0f));

    // 地面(Y=0)との交点
    float t = -nearPos.y / (farPos.y - nearPos.y);

    VECTOR hitPos;
    hitPos.x = nearPos.x + (farPos.x - nearPos.x) * t;
    hitPos.y = 0.0f;
    hitPos.z = nearPos.z + (farPos.z - nearPos.z) * t;

    selectNode = -1;
    float minDist = 40.0f;

    for (int i = 0; i < nodes.size(); i++)
    {
        float dx = hitPos.x - nodes[i].x;
        float dz = hitPos.z - nodes[i].z;

        float dist = sqrtf(dx * dx + dz * dz);

        if (dist < minDist)
        {
            minDist = dist;
            selectNode = i;
        }
    }
}
