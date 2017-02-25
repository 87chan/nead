#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SceneBase.h"

class MyContactListener;
class MyController;
class MyFieldManager;
class MyBallManager;
class GimmickManager;
class MyDrawNode;
class MyBall;
class MyGoal;

enum GAME_STATE
{
	NONE,

	MAIN,
	GAME_CLEAR,
	GAME_OVER,

	MAX,
};

class SceneGameMain : public SceneBase
{
public:
	SceneGameMain();
	~SceneGameMain() {}

	void Initialize() override;
	void update(float delta) override;

	void Start();

	void ClearCallback();
	void GameOverCallback();
	void GameEnd(GAME_STATE state);

	void RetryCallBack(Ref* pSender);
	void ReturnCallBack(Ref* pSender);

private:
	b2World* World;
	MyController*					Controller;

	MyFieldManager*					FieldMgr;
	std::shared_ptr<MyBallManager>	BallMgr;
	std::shared_ptr<GimmickManager>	GimmickMgr;
	MyBall*							BallNode1;
	MyBall*							BallNode2;
	MyGoal*							GoalNode;
	MyDrawNode*						LineShotDirection;

	cocos2d::LabelTTF*				GameEndrLabel;
	bool							bClear;
};

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
