#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "MyDrawNode.h"

class GimmickBase : public MyDrawNode
{
public:
	GimmickBase();
	virtual ~GimmickBase() {}

	virtual void Initialize(b2World* world, cocos2d::Layer* parentLayer) override;
	virtual void Finalize(b2World* world, cocos2d::Layer* parentLayer) override;
	virtual void UpdateBody(float dt) override;

	// 何かに触れられた時に呼ばれる処理.
	virtual void OnContactBegin() {};
	
	// 何かが離れた時に呼ばれる処理.
	virtual void OnContactEnd() {};
};

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
