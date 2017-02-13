#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "MyBallManager.h"

class MyContactListener;
class MyController;
class MyFieldManager;
class MyBallManager;
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

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

	HelloWorld();
	virtual ~HelloWorld() {}

    virtual bool init();
  
	void initPhysics();
	void update(float dt);

	void start();

	void ClearCallback();
	void GameOverCallback();
	void GameEnd(GAME_STATE state);

    void retryCallBack(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	b2World* World;

	MyContactListener*				ContactListener;
	MyController*					Controller;

	MyFieldManager*					FieldMgr;
	std::shared_ptr<MyBallManager>	BallMgr;
	MyBall*							BallNode1;
	MyBall*							BallNode2;
	MyGoal*							GoalNode;
	MyDrawNode*						LineShotDirection;

	cocos2d::LabelTTF*				GameEndrLabel;
	bool							bClear;
};

#endif // __HELLOWORLD_SCENE_H__
