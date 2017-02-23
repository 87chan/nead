#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class MyBallManager;

class MyController : public cocos2d::Layer
{
public:
	MyController();
	~MyController();

	void Initialize(b2World* world);
	void EntryBallMgr(MyBallManager* ballMgr);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	bool			GetIsTouch() const { return bTouch; }
	cocos2d::Vec2	GetTouchPos() const { return TouchPos; }
	cocos2d::Vec2	GetMovePos() const { return MovePos; }
	cocos2d::Vec2	GetShotDirection() const { return ShotDirection; }

private:
	b2World*					WorldRef;
	MyBallManager*				BallMgrRef;

	bool						bTouch;

	cocos2d::Vec2				TouchPos;
	cocos2d::Vec2				MovePos;
	cocos2d::Vec2				ShotDirection;
};

/**************************************************************************************************
* EOF
**************************************************************************************************/
