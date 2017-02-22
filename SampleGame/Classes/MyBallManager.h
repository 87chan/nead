#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "MyBall.h"
#include "AppHeader.h"

class MyBallManager
{
public:
	MyBallManager();
	~MyBallManager();

	void EntryBallNode(MyBall* ball);
	void Finalize(b2World* world, cocos2d::CCNode* parentNode);
	void Update(float dt);

	bool CheckAllFinish();

	void ResetAllSelected();

	void ResetCallback() { CC_SAFE_DELETE(callbackGameOver); }

	template <class C, class T>
	void SetCallback(C& obj, T func)
	{
		callbackGameOver = new MyCallback<C, T>(obj, func);
	}

	void ExecuteCallback() { callbackGameOver->Execute(); }

	std::vector<MyBall*> GetBallList() { return BallNodeList; }
	MyBall* GetSelectedBall();
	MyBall* GetBall(const cocos2d::Vec2& pos);

private:
	std::vector<MyBall*> BallNodeList;
	MyCallbackBase* callbackGameOver;
};

/**************************************************************************************************
* EOF
**************************************************************************************************/
