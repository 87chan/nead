#include "MyController.h"
#include "AppHeader.h"
#include "MyBall.h"
#include "MyBallManager.h"

USING_NS_CC;

MyController::MyController()
: WorldRef(nullptr)
, BallMgrRef(nullptr)
, bTouch(false)
, TouchPos()
, MovePos()
, ShotDirection()
{
}

MyController::~MyController()
{
}

void MyController::Initialize(b2World* world)
{
	WorldRef = world;

	//イベントリスナーを作成
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(MyController::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MyController::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MyController::onTouchEnded, this);

	//イベントリスナーを登録
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}

void MyController::EntryBallMgr(MyBallManager* ballMgr)
{
	BallMgrRef = ballMgr;
}

bool MyController::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if (MyBall* ball = BallMgrRef->GetSelectedBall())
	{
		if (ball->IsPossibleShot())
		{
			bTouch = true;

			TouchPos = touch->getLocation();
			MovePos = TouchPos;
		}
	}

	return true;
}

void MyController::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	MovePos = touch->getLocation();

	// 発射方向の更新.
	ShotDirection = (TouchPos - MovePos);
}

void MyController::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	bTouch = false;

	b2Vec2 shotDirection = b2Vec2(ShotDirection.x, ShotDirection.y);
	float length = std::min(shotDirection.Length(), MAX_LENGTH);
	shotDirection.Normalize();

	if (BallMgrRef)
	{
		if (ShotDirection.length() <= SELECT_LENGTH_THRESHOULD)
		{
			// 選択処理.
			Vec2 touchPoint = touch->getLocation();

			if (MyBall* ball = BallMgrRef->GetBall(touchPoint))
			{
				BallMgrRef->ResetAllSelected();
				ball->SetSelect(true);
			}
		}
		else
		{
			// 現在選択されているボールに対して力を加える.
			if (MyBall* ball = BallMgrRef->GetSelectedBall())
			{
				if (ball->IsPossibleShot())
				{
					static float POWER_RATE = 1.0f;
					const b2Vec2 force = shotDirection * length * POWER_RATE;
					ball->OnShot(force);

					// 発射.
					log("[%f,%f]の方向に長さ[%f]を発射", ShotDirection.x, ShotDirection.y, length);
				}
			}
		}
	}

	ShotDirection = Vec2::ZERO;
}

/**************************************************************************************************
* EOF
**************************************************************************************************/
