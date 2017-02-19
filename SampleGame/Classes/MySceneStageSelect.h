#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class MySceneStageSelect : public cocos2d::Scene
{
public:
	MySceneStageSelect();
	~MySceneStageSelect();

	CREATE_FUNC(MySceneStageSelect);

	static cocos2d::Scene* createScene();

	bool init();
	void update(float dt);
	void InitLabel();

	void TouchStageItem(Ref* pSender);

private:
};

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
