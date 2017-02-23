#include "SceneBase.h"

USING_NS_CC;

SceneBase::SceneBase()
{
}

SceneBase::~SceneBase()
{
}

bool SceneBase::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// 基本的に更新を行う.
	this->scheduleUpdate();

	this->Initialize();

	return true;
}

void SceneBase::update(float delta)
{
	CCNode::update(delta);
}

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
