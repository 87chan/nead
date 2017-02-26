#include "SceneGameMain.h"
#include "SimpleAudioEngine.h"
#include "AppHeader.h"
#include "MySceneStageSelect.h"
#include "GlobalInfo.h"
#include "Collision/MyContactListener.h"
#include "Controller/MyController.h"
#include "Node/MyDrawNode.h"
#include "Ball/MyBallManager.h"
#include "Stage/MyFieldManager.h"
#include "Gimmick/GimmickManager.h"
#include "Gimmick/GimmickAccelerate.h"
#include "Gimmick/GimmickGoal.h"

USING_NS_CC;

SceneGameMain::SceneGameMain()
: World(nullptr)
, Controller(nullptr)
, FieldMgr(nullptr)
, BallNode1(nullptr)
, BallNode2(nullptr)
, LineShotDirection(nullptr)
, GameEndLabel(nullptr)
, bClear(false)
{
}

void SceneGameMain::Initialize()
{
	SceneBase::Initialize();

	Size size = Director::getInstance()->getWinSize();

	//ワールド生成  
	b2Vec2 gravity = b2Vec2(0, -9.8f);
	World = new b2World(gravity);
	World->SetAllowSleeping(true);
	World->SetContinuousPhysics(true);

	// 衝突を検知する.
	World->SetContactListener(MyContactListener::GetInstance());

	GameEndLabel = cocos2d::LabelTTF::create("", "Arial", 24);
	GameEndLabel->setPosition(size.width * 0.5f, size.height * 0.5f);
	GameEndLabel->setVisible(false);
	this->addChild(GameEndLabel);

	// リトライボタンを作成.
	MenuItemImage* retryItem = MenuItemImage::create(
		"replay1.png",
		"replay2.png",
		CC_CALLBACK_1(SceneGameMain::RetryCallBack, this));
	Menu* menuRetry = Menu::create(retryItem, NULL);
	menuRetry->setPosition(0.0f + retryItem->getContentSize().width * 0.5f, size.height - retryItem->getContentSize().height * 0.5f);
	this->addChild(menuRetry, MENU_LAYER);

	// 戻るボタンを作成.
	MenuItemImage* returnItem = MenuItemImage::create(
		"back1.png",
		"back2.png",
		CC_CALLBACK_1(SceneGameMain::ReturnCallBack, this));
	Menu* menuReturn = Menu::create(returnItem, NULL);
	menuReturn->setPosition(size.width - returnItem->getContentSize().width * 0.5f, size.height - returnItem->getContentSize().height * 0.5f);
	this->addChild(menuReturn, MENU_LAYER);

	this->Start();
}

void SceneGameMain::update(float delta)
{
	SceneBase::update(delta);

	World->Step(delta, VELOCITY_ITERATIONS, POSITION_ITERATIONS);    //フレームごとにWorldの情報を更新

	BallMgr->Update(delta);

	GimmickMgr->Update(delta);

	// ガイドの更新.
	float length = std::min(Controller->GetShotDirection().length(), MAX_LENGTH);
	cocos2d::Vec2 shotDirection = Controller->GetShotDirection();
	shotDirection.normalize();

	if (MyBall* ball = BallMgr->GetSelectedBall())
	{
		Vec2 playerPos = ball->GetSpritePos();
		Vec2 forwardPos = playerPos + (shotDirection * length * 0.5f);
		Vec2 backPos = playerPos + (-shotDirection * length * 0.5f);

		LineShotDirection->Clear();

		if (Controller->GetIsTouch())
		{
			LineShotDirection->DrawLine(backPos, forwardPos, ccColor4F::BLUE);
		}
	}
}

void SceneGameMain::Start()
{
	//絶対に子にする必要はないが、子にするとタイルレイヤーがそのまま表示される。
	std::string filePath = GlobalInfo::GetInstance()->stagePath;
	TMXTiledMap* pMap = TMXTiledMap::create(filePath);
	this->addChild(pMap);

	// コールバックの解除.
	MyContactListener::GetInstance()->RemoveContactCallback();

	if (!Controller)
	{
		Controller = new MyController();
		Controller->Initialize(World);
		this->addChild(Controller);
	}

	// フィールド.
	if (FieldMgr)
	{
		FieldMgr->Finalize(World, this);
	}
	FieldMgr = MyFieldManager::create();
	FieldMgr->Initialize(World, this);

	// ボール管理者.
	if (BallMgr)
	{
		BallMgr->Finalize(World, this);
	}
	BallMgr.reset(new MyBallManager());
	Controller->EntryBallMgr(BallMgr.get());
	BallMgr->ResetCallback();
	BallMgr->SetCallback(this, &SceneGameMain::GameOverCallback);

	Vec2 ballPos_1, ballPos_2;
	bool bSelect_1 = false, bSelect_2 = false;
	int shotNum_1 = 0, shotNum_2 = 0;
	Vec2 goalPos;
	float goalSize;
	//オブジェクトの位置取得
	auto pObjectGroup = pMap->getObjectGroup("ObjectLayer1");
	if (pObjectGroup)
	{
		{
			auto ballInfo = pObjectGroup->getObject("ball1");
			ballPos_1.x = ballInfo["x"].asFloat();
			ballPos_1.y = ballInfo["y"].asFloat();
			bSelect_1 = ballInfo["bSelect"].asBool();
			shotNum_1 = ballInfo["shotNum"].asInt();
		}
		{
			auto ballInfo2 = pObjectGroup->getObject("ball2");
			ballPos_2.x = ballInfo2["x"].asFloat();
			ballPos_2.y = ballInfo2["y"].asFloat();
			bSelect_2 = ballInfo2["bSelect"].asBool();
			shotNum_2 = ballInfo2["shotNum"].asInt();
		}
		{
			auto goalInfo = pObjectGroup->getObject("goal");
			goalPos.x = goalInfo["x"].asFloat();
			goalPos.y = goalInfo["y"].asFloat();
			goalSize = goalInfo["width"].asFloat();
		}
	}

	// ボール1.
	BallNode1 = MyBall::create();
	BallNode1->Initialize(World, this, BallMgr, ballPos_1, shotNum_1);
	BallNode1->SetSelect(bSelect_1);
	BallMgr->EntryBallNode(BallNode1);

	// ボール2.
	BallNode2 = MyBall::create();
	BallNode2->Initialize(World, this, BallMgr, ballPos_2, shotNum_2);
	BallNode2->SetSelect(bSelect_2);
	BallMgr->EntryBallNode(BallNode2);

	// ギミック管理者.
	if (GimmickMgr)
	{
		GimmickMgr->Finalize();
	}
	GimmickMgr.reset(new GimmickManager());
	GimmickMgr->Initialize(World, this);

	// 加速ギミック.
	GimmickMgr->CreateGimmick<GimmickAccelerate>(BallMgr.get(), Vec2(500.0f, 100.0f), 32);

	// ゴールギミック.
	GimmickMgr->CreateGimmick<GimmickGoal>(BallMgr.get(), goalPos, goalSize * 0.5f);

	// ガイド.
	if (LineShotDirection)
	{
		LineShotDirection->Finalize(World, this);
	}
	LineShotDirection = MyDrawNode::create();
	LineShotDirection->setLocalZOrder(UI_LAYER);
	LineShotDirection->Initialize(World, this);
}

void SceneGameMain::ClearCallback()
{
	this->GameEnd(GAME_STATE::GAME_CLEAR);
}

void SceneGameMain::GameOverCallback()
{
	this->GameEnd(GAME_STATE::GAME_OVER);
}

void SceneGameMain::GameEnd(GAME_STATE state)
{
	Director::getInstance()->pause();

	std::string str = "";
	switch (state)
	{
	case GAME_STATE::GAME_CLEAR:
		str = "Game Clear";
		break;
	case GAME_STATE::GAME_OVER:
		str = "Game Over";
		break;
	default:
		break;
	}

	GameEndLabel->setString(str);
	GameEndLabel->setVisible(true);
	bClear = true;
}

void SceneGameMain::RetryCallBack(Ref* pSender)
{
	this->Start();
	Director::getInstance()->resume();
	GameEndLabel->setVisible(false);
	bClear = false;
}

void SceneGameMain::ReturnCallBack(Ref* pSender)
{
	Director::getInstance()->resume();

	SceneUtil::TransitionScene<MySceneStageSelect, TransitionFade>(1.0f);
}

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
