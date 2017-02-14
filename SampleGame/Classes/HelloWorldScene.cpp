#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MyBall.h"
#include "AppHeader.h"
#include "MyGoal.h"
#include "MyFieldManager.h"
#include "MyController.h"
#include "MyContactListener.h"
#include "MyBallManager.h"
#include "MySceneStageSelect.h"

USING_NS_CC;

HelloWorld::HelloWorld()
: World(nullptr)
, ContactListener(nullptr)
, Controller(nullptr)
, FieldMgr(nullptr)
, BallNode1(nullptr)
, BallNode2(nullptr)
, GoalNode(nullptr)
, LineShotDirection(nullptr)
, GameEndrLabel(nullptr)
, bClear(false)
{
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	this->initPhysics();
	this->scheduleUpdate();

	Size size = Director::getInstance()->getWinSize();
	GameEndrLabel = cocos2d::LabelTTF::create("", "Arial", 24);
	GameEndrLabel->setPosition(size.width * 0.5f, size.height * 0.5f);
	GameEndrLabel->setVisible(false);
	this->addChild(GameEndrLabel);

	// リトライボタンを作成.
	MenuItemImage* retryItem = MenuItemImage::create(
		"replay1.png",
		"replay2.png",
		CC_CALLBACK_1(HelloWorld::RetryCallBack, this));
	Menu* menuRetry = Menu::create(retryItem, NULL);
	menuRetry->setPosition(0.0f + retryItem->getContentSize().width * 0.5f, size.height - retryItem->getContentSize().height * 0.5f);
	this->addChild(menuRetry, MENU_LAYER);

	// 戻るボタンを作成.
	MenuItemImage* returnItem = MenuItemImage::create(
		"back1.png",
		"back2.png",
		CC_CALLBACK_1(HelloWorld::ReturnCallBack, this));
	Menu* menuReturn = Menu::create(returnItem, NULL);
	menuReturn->setPosition(size.width - returnItem->getContentSize().width * 0.5f, size.height - returnItem->getContentSize().height * 0.5f);
	this->addChild(menuReturn, MENU_LAYER);

	this->start();

    return true;
}

void HelloWorld::initPhysics()
{
	//ワールド生成  
	b2Vec2 gravity = b2Vec2(0, -9.8f);
	World = new b2World(gravity);
	World->SetAllowSleeping(true);
	World->SetContinuousPhysics(true);

	// 衝突を検知する.
	ContactListener = new MyContactListener();
	World->SetContactListener(ContactListener);
}

void HelloWorld::update(float dt)
{
	World->Step(dt, VELOCITY_ITERATIONS, POSITION_ITERATIONS);    //フレームごとにWorldの情報を更新

	BallMgr->Update(dt);

	// ガイドの更新.
	float length = std::min(Controller->GetShotDirection().length(), MAX_LENGTH);
	cocos2d::Vec2 shotDirection = Controller->GetShotDirection();
	shotDirection.normalize();

	if (MyBall* ball = BallMgr->GetSelectedBall())
	{
		Vec2 playerPos = ball->GetSpritePos();
		Vec2 forwardPos = playerPos + (shotDirection * length * 0.5f);
		Vec2 backPos = playerPos + (-shotDirection * length * 0.5f);

		LineShotDirection->clear();

		if (Controller->GetIsTouch())
		{
			LineShotDirection->drawLine(backPos, forwardPos, ccColor4F::BLUE);
		}
	}
}

void HelloWorld::start()
{
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
	if (!BallMgr)
	{
		BallMgr.reset(new MyBallManager());
		Controller->EntryBallMgr(BallMgr.get());

		BallMgr->ResetCallback();
		BallMgr->SetCallback(this,&HelloWorld::GameOverCallback);
	}
	BallMgr->Finalize(World, this);

	// ボール1.
	BallNode1 = MyBall::create();
	BallNode1->Initialize(World, this, BallMgr, Vec2(10, 8));
	BallNode1->SetSelect(true);
	BallMgr->EntryBallNode(BallNode1);

	// ボール2.
	BallNode2 = MyBall::create();
	BallNode2->Initialize(World, this, BallMgr, Vec2(50, 8));
	BallMgr->EntryBallNode(BallNode2);

	// ゴール.
	if (GoalNode)
	{
		GoalNode->Finalize(World, this);
	}
	GoalNode = MyGoal::create();
	GoalNode->Initialize(World, this);

	// 衝突時のコールバック登録.
	ContactListener->RemoveContactCallback();
	std::vector<MyBall*> list = BallMgr->GetBallList();
	std::vector<MyBall*>::iterator it = list.begin();
	for (; it != list.end(); ++it)
	{
		if (MyBall* ball = (*it))
		{
			ContactEntryParam param = ContactEntryParam();
			param.body1 = ball->GetBodyData();
			param.body2 = GoalNode->GetBodyData();
			param.SetCallback(this, &HelloWorld::ClearCallback);
			ContactListener->EntryContactCallBack(param);
		}
	}

	// ガイド.
	if (LineShotDirection)
	{
		LineShotDirection->Finalize(World, this);
	}
	LineShotDirection = MyDrawNode::create();
	LineShotDirection->setLocalZOrder(UI_LAYER);
	LineShotDirection->Initialize(World, this);
}

void HelloWorld::ClearCallback()
{
	this->GameEnd(GAME_STATE::GAME_CLEAR);
}

void HelloWorld::GameOverCallback()
{
	this->GameEnd(GAME_STATE::GAME_OVER);
}

void HelloWorld::GameEnd(GAME_STATE state)
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

	GameEndrLabel->setString(str);
	GameEndrLabel->setVisible(true);
	bClear = true;
}

void HelloWorld::RetryCallBack(Ref* pSender)
{
	this->start();
	Director::getInstance()->resume();
	GameEndrLabel->setVisible(false);
	bClear = false;
}

void HelloWorld::ReturnCallBack(Ref* pSender)
{
	Director::getInstance()->resume();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MySceneStageSelect::createScene()));
}

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
