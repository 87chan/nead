#pragma once

/**************************************************************************************************
*\	フィールドのオブジェクトを管理するクラス.
*	できれば「Node」系は継承させず、管理に集中させたい.
**************************************************************************************************/

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Node/MyNode.h"

class MyFieldManager : public MyNode
{
public:
	MyFieldManager();
	~MyFieldManager();

	CREATE_FUNC(MyFieldManager);

	void Initialize(b2World* world, cocos2d::CCNode* parentNode) override;
	void Finalize(b2World* world, cocos2d::CCNode* parentNode) override;

	void CreateFrame(b2World* world);

	b2Body*	GetFrameBody() { return FrameBody; }

private:
	b2Body*	FrameBody;
};

/**************************************************************************************************
*\	EOF
**************************************************************************************************/
