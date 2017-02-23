#include "GimmickManager.h"

GimmickManager::GimmickManager()
{
}

void GimmickManager::Initialize(b2World* world, cocos2d::CCNode* parentNode)
{
	WorldRef = world;
	ParentRef = parentNode;
}

void GimmickManager::Finalize()
{
	for (int i = 0; i < GimmickList.size(); ++i)
	{
		if (GimmickBase* gimmick = GimmickList[i])
		{
			gimmick->Finalize(WorldRef, ParentRef);
		}
	}

	GimmickList.clear();
}

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
