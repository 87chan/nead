#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class MySceneTitle : public cocos2d::Scene
{
public:
	MySceneTitle();
	virtual ~MySceneTitle();

	CREATE_FUNC(MySceneTitle);

	static cocos2d::Scene* createScene();

	bool init();
	void update(float dt);
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
