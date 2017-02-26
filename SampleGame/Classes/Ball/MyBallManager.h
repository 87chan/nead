#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "MyBall.h"
#include "AppHeader.h"
#include "ManagerBase/ManagerBase.h"

class MyBallManager : public ManagerBase
{
public:
	MyBallManager();
	~MyBallManager() {}

	void Initialize(b2World* world, cocos2d::CCNode* parentNode) override;
	void Update(float delta) override;
	void Finalize() override;

	// �{�[�������֐�.
	void CreateBall(const cocos2d::Vec2& pos, int shotNum, bool select);

	// �S�Ă̋ʂ̎c�����u0�v�ɂȂ�����.
	bool CheckAllFinish();

	// �S�Ă̋ʂ̑I����Ԃ�������.
	void ResetAllSelected();

	std::vector<MyBall*> GetBallList() { return BallNodeList; }
	MyBall* GetSelectedBall();
	MyBall* GetBall(const cocos2d::Vec2& pos);

private:
	std::vector<MyBall*> BallNodeList;
};

/**************************************************************************************************
* EOF
**************************************************************************************************/
