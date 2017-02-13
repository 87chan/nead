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

	void Initialize(b2World* world, cocos2d::Layer* parentLayer) override;
	void Finalize(b2World* world, cocos2d::Layer* parentLayer) override;
};

/**************************************************************************************************
* EOF
**************************************************************************************************/
