#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GimmickBase.h"

class GimmickGravity : public GimmickBase
{
public:
	GimmickGravity();
	~GimmickGravity() {}

	void Initialize(b2World* world, cocos2d::CCNode* parentNode, const cocos2d::Vec2& pos, float size);
	void Finalize(b2World* world, cocos2d::CCNode* parentNode) override;
	void UpdateBody(float dt) override;

	void OnContactBegin(b2Body* body1, b2Body* body2) override;
};

