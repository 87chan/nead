#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SceneBase.h"

class MySceneStageSelect : public SceneBase
{
public:
	MySceneStageSelect();
	~MySceneStageSelect();

	void Initialize() override;
	void update(float delta);
	void InitLabel();

	void TouchStageItem(Ref* pSender);

private:
};

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
