#pragma once

#include "cocos2d.h"

class GimmickBase;

class GimmickManager
{
public:
	GimmickManager();
	~GimmickManager();

	// ÉMÉ~ÉbÉNÇçÏê¨.
	template<class T>
	void CreateGimmick(T gimmick)
	{
		GimmickBase* gimmick = T::create();
		CC_ASSERT(gimmck);

		GimmickList.push_back(gimmick);
	}

private:
	std::vector<GimmickBase*> GimmickList;
};

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
