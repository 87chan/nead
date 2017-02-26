#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GimmickBase.h"

// 触れたらステージクリア.
// Todo:世界観に合わせて、吸い込まれるような表現等を取り入れる.

class GimmickGoal : public GimmickBase
{
public:
	GimmickGoal();
	~GimmickGoal() {}

	void Initialize(b2World* world, cocos2d::CCNode* parentNode, const cocos2d::Vec2& pos, float size) override;
	void Finalize(b2World* world, cocos2d::CCNode* parentNode) override;
	void UpdateBody(float dt) override;

	void OnContactBegin(b2Body* body1, b2Body* body2) override;
};

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
