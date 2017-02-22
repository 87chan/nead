#pragma once

#include "MyDrawNode.h"
#include "cocos2d.h"
#include "Box2D/Box2D.h"

class MyGoal : public MyDrawNode
{
public:
	MyGoal();
	~MyGoal();

	CREATE_FUNC(MyGoal);

    void InitParamInfo(const cocos2d::Vec2& pos, float size);
	void Initialize(b2World* world, cocos2d::CCNode* parentNode) override;
	void Finalize(b2World* world, cocos2d::CCNode* parentNode) override;
private:
    cocos2d::Vec2 GoalPos;
    float GoalSize;
};

/**************************************************************************************************
* EOF
**************************************************************************************************/
