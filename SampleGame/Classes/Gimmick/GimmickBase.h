#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Node/MyDrawNode.h"

class GimmickManager;

class GimmickBase : public MyDrawNode
{
public:
	GimmickBase();
	virtual ~GimmickBase() {}

	virtual void Initialize(b2World* world, cocos2d::CCNode* parentNode, const cocos2d::Vec2& pos, float size);
	virtual void Finalize(b2World* world, cocos2d::CCNode* parentNode) override;
	virtual void UpdateBody(float delta) override;
	virtual void Update(float delta) override;

	// 何かに触れられた時に呼ばれる処理.
	virtual void OnContactBegin(b2Body* body1, b2Body* body2) {}
	
	// 何かが離れた時に呼ばれる処理.
	virtual void OnContactEnd(b2Body* body1, b2Body* body2) {}
};

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
