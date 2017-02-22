#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SceneBase.h"

class MySceneTitle : public SceneBase
{
public:
	MySceneTitle();
	virtual ~MySceneTitle();

	void Initialize() override;
	void update(float delta) override;
	void InitLabel();

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

private:
	cocos2d::LabelTTF*			TitleLabel;
	cocos2d::LabelTTF*			GuideLabel;
	GLubyte						GuideOpacity;
	float						TimeCount;
};

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
