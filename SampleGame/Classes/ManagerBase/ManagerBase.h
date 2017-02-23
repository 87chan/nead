#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class ManagerBase
{
public:
	ManagerBase();
	virtual ~ManagerBase() {}

	virtual void Initialize(b2World* world, cocos2d::CCNode* parentNode);
	virtual void Update(float delta) {}
	virtual void Finalize() {}

protected:
	b2World*			WorldRef;
	cocos2d::CCNode*	ParentRef;
};

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
