#include "ManagerBase.h"

ManagerBase::ManagerBase()
{
}

void ManagerBase::Initialize(b2World* world, cocos2d::CCNode* parentNode)
{
	WorldRef = world;
	ParentRef = parentNode;
}

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
