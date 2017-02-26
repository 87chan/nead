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

	// ボール生成関数.
	void CreateBall(const cocos2d::Vec2& pos, int shotNum, bool select);

	// 全ての玉の残数が「0」になったか.
	bool CheckAllFinish();

	// 全ての玉の選択状態を初期化.
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
