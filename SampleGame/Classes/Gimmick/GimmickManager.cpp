#include "GimmickManager.h"

GimmickManager::GimmickManager()
{
}

void GimmickManager::Initialize(b2World* world, cocos2d::CCNode* parentNode)
{
	ManagerBase::Initialize(world, parentNode);
}

void GimmickManager::Update(float delta)
{
	ManagerBase::Update(delta);
}

void GimmickManager::Finalize()
{
	std::vector<GimmickBase*>::iterator it = GimmickList.begin();
	for (; it != GimmickList.end(); ++it)
	{
		(*it)->Finalize(WorldRef, ParentRef);
	}

	GimmickList.clear();
}

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
