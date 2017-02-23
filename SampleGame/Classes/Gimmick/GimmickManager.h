#pragma once

#include "cocos2d.h"
#include "AppHeader.h"
#include "GimmickBase.h"

class GimmickManager
{
public:
	GimmickManager();
	~GimmickManager() {}

	void Initialize(b2World* world, cocos2d::CCNode* parentNode);
	void Finalize();

	// ÉMÉ~ÉbÉNÇçÏê¨.
	template<class T>
	void CreateGimmick()
	{
		GimmickBase* gimmick = AppUtil::createNode<T>();
		CC_ASSERT(gimmick);

		gimmick->Initialize(WorldRef, ParentRef);

		GimmickList.push_back(gimmick);
	}

private:
	b2World*					WorldRef;
	cocos2d::CCNode*			ParentRef;

	std::vector<GimmickBase*>	GimmickList;
};

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
