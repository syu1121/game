#include "SceneFactory.h"
#include <windows.h>
#include <assert.h>
#include "BootScene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "StageSelectScene.h"
#include "EnemyScene.h"
SceneBase* SceneFactory::CreateFirst()
{
	return new BootScene();
}

SceneBase * SceneFactory::Create(const std::string & name)
{
	if (name == "TITLE")
	{
		return new TitleScene();
	}
	if (name == "STAGESELECT")
	{
		return new StageSelectScene();
	}
	if (name == "PLAY")
	{
		return new PlayScene();
	}
	if (name == "ENEMY SCENE")
	{
		return new EnemyScene();
	}
	if (name == "RESULT")
	{
		return new ResultScene();
	}
	MessageBox(NULL, ("éüÇÃÉVÅ[ÉìÇÕÇ†ÇËÇ‹ÇπÇÒ\n" + name).c_str(), "SceneFactory", MB_ICONERROR | MB_OK);
	assert(false);
	return nullptr;
}
