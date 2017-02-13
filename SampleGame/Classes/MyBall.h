#pragma once

#include "MySpriteNode.h"
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "MyDrawNode.h"

class MyBallManager;

class MyBall : public MySpriteNode
{
public:
	MyBall();
	~MyBall();

	CREATE_FUNC(MyBall);

	void Initialize(b2World* world, cocos2d::Layer* parentLayer, std::shared_ptr<MyBallManager> ballMgr, const cocos2d::Vec2& pos);
	void Finalize(b2World* world, cocos2d::Layer* parentLayer) override;
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
	std::shared_ptr<MyBallManager>	BallMgrRef;

	cocos2d::CCSpriteBatchNode*		SpriteBatchNode;

	cocos2d::LabelTTF*				LabelShotNum;
	MyDrawNode*						CircleSelected;
	
	bool							bSelected;				// 選択されているか.
	bool							bStandby;				// 発射準備が出来たか.
	int								LeftShotNum;			// 残り発射回数.
};

/**************************************************************************************************
* EOF
**************************************************************************************************/
