#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Node/MyDrawNode.h"
#include "Node/MySpriteNode.h"

class MyBallManager;

class MyBall : public MySpriteNode
{
public:
	MyBall();
	~MyBall();

	CREATE_FUNC(MyBall);

	void Initialize(b2World* world, cocos2d::CCNode* parentNode, MyBallManager* ballMgr, const cocos2d::Vec2& pos,int shotNum);
	void Finalize(b2World* world, cocos2d::CCNode* parentNode) override;
	void Update(float dt);
	void UpdateShotNum();
	void OnShot(const b2Vec2& force);

	bool IsZeroLeftShotNum() const { return (LeftShotNum <= 0); }
	bool GetIsSelected() const { return bSelected; }
	bool IsPossibleShot() const { return(bSelected && bStandby && !this->IsZeroLeftShotNum()); }
	bool IsFinished() const { return bStandby && this->IsZeroLeftShotNum(); }
	void ConsumeLeftShotNum() { --LeftShotNum; }
	void SetSelect(bool select) { bSelected = select; }

private:
	MyBallManager*					BallMgrRef;

	cocos2d::CCSpriteBatchNode*		SpriteBatchNode;

	cocos2d::LabelTTF*				LabelShotNum;
	MyDrawNode*						CircleSelected;
	
	bool							bSelected;				// ëIëÇ≥ÇÍÇƒÇ¢ÇÈÇ©.
	bool							bStandby;				// î≠éÀèÄîıÇ™èoóàÇΩÇ©.
	int								LeftShotNum;			// écÇËî≠éÀâÒêî.
};

/**************************************************************************************************
* EOF
**************************************************************************************************/
