#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GimmickBase.h"

class GimmickAccelerate : public GimmickBase
{
public:
	GimmickAccelerate();
	~GimmickAccelerate();

	void Initialize(b2World* world, cocos2d::CCNode* parentNode) override;
	void Finalize(b2World* world, cocos2d::CCNode* parentNode) override;
	void UpdateBody(float dt) override;

	void OnContactBegin();
};

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
