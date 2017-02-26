#pragma once

#include "cocos2d.h"
#include "AppHeader.h"
#include "GimmickBase.h"
#include "ManagerBase/ManagerBase.h"

class MyBallManager;

class GimmickManager : ManagerBase
{
public:
	GimmickManager();
	~GimmickManager() {}

	void Initialize(b2World* world, cocos2d::CCNode* parentNode) override;
	void Update(float delta) override;
	void Finalize() override;

	// ギミックを作成.
	template<class T>
	void CreateGimmick(MyBallManager* ballMgr, cocos2d::Vec2 pos,float size)
	{
		GimmickBase* gimmick = AppUtil::createNode<T>();
		CC_ASSERT(gimmick);

		gimmick->Initialize(WorldRef, ParentRef, pos, size);

		// ボールの数だけコールバックを設定.
		std::vector<MyBall*> ballList = ballMgr->GetBallList();
		std::vector<MyBall*>::iterator it = ballList.begin();
		for (; it != ballList.end(); ++it)
		{
			if (MyBall* ball = (*it))
			{
				ContactEntryParam param;
				param.body1 = ball->GetBodyData();
				param.body2 = gimmick->GetBodyData();

				param.timing = ContactTiming::BEGIN;
				param.callback = CC_CALLBACK_2(GimmickBase::OnContactBegin, gimmick);
				MyContactListener::GetInstance()->EntryContactCallBack(param);

				param.timing = ContactTiming::END;
				param.callback = CC_CALLBACK_2(GimmickBase::OnContactEnd, gimmick);
				MyContactListener::GetInstance()->EntryContactCallBack(param);
			}
		}

		GimmickList.push_back(gimmick);
	}

private:
	std::vector<GimmickBase*>	GimmickList;
};

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
