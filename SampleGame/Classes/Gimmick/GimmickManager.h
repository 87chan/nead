#pragma once

#include "cocos2d.h"
#include "AppHeader.h"
#include "GimmickBase.h"
#include "ManagerBase/ManagerBase.h"

class GimmickManager : ManagerBase
{
public:
	GimmickManager();
	~GimmickManager() {}

	void Initialize(b2World* world, cocos2d::CCNode* parentNode) override;
	void Update(float delta) override;
	void Finalize() override;

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
	std::vector<GimmickBase*>	GimmickList;
};

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
