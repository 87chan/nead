#include "MySceneTitle.h"
#include "MySceneStageSelect.h"

USING_NS_CC;

static GLubyte		OPACITY_MAX = 255;
static const float	OPACITY_ANIMATION_TIME = 2.0f;

MySceneTitle::MySceneTitle()
: TitleLabel(nullptr)
, GuideLabel(nullptr)
, GuideOpacity(255)
, TimeCount(0.0f)
{
}

MySceneTitle::~MySceneTitle()
{
}

Scene* MySceneTitle::createScene()
{
	auto sceneTitle = MySceneTitle::create();
	return sceneTitle;
}

bool MySceneTitle::init()
{
	if (!Scene::init())
	{
		return false;
	}

	//イベントリスナーの設定.
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MySceneTitle::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(MySceneTitle::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	this->InitLabel();

	this->scheduleUpdate();

	return true;
}

void MySceneTitle::update(float dt)
{
	TimeCount += dt;
	if (OPACITY_ANIMATION_TIME <= TimeCount)
	{
		float sub = TimeCount - OPACITY_ANIMATION_TIME;
		TimeCount = sub;
	}
	float ration = 1.0f - (TimeCount / OPACITY_ANIMATION_TIME);

	GuideLabel->setOpacity(OPACITY_MAX * ration);
}

void MySceneTitle::InitLabel()
{
	Size size = Director::getInstance()->getWinSize();
	
	TitleLabel = cocos2d::LabelTTF::create("nead", "Arial", 40);
	TitleLabel->setPosition(size.width * 0.5f, size.height * 0.6f);
	TitleLabel->setVisible(true);
	this->addChild(TitleLabel);

	GuideLabel = cocos2d::LabelTTF::create("Tap To Start", "Arial", 20);
	GuideLabel->setPosition(size.width * 0.5f, size.height * 0.2f);
	GuideLabel->setVisible(true);
	GuideLabel->setOpacity(GuideOpacity);
	this->addChild(GuideLabel);
}

bool MySceneTitle::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	return true;
}
 
void MySceneTitle::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MySceneStageSelect::createScene()));
}

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
