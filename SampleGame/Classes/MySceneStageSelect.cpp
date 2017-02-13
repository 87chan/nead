#include "MySceneStageSelect.h"
#include "HelloWorldScene.h"

USING_NS_CC;

static const int TEST_STAGE_NUM = 3;
static const int TEST_STAGE_OFFSET = 50.0f;

MySceneStageSelect::MySceneStageSelect()
{
}

MySceneStageSelect::~MySceneStageSelect()
{
}

Scene* MySceneStageSelect::createScene()
{
	auto sceneTitle = MySceneStageSelect::create();
	return sceneTitle;
}

bool MySceneStageSelect::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Size size = Director::getInstance()->getWinSize();

	for (int i = 0; i < TEST_STAGE_NUM; ++i)
	{
		std::string str = "Stage";
		char sNum[32];
		sprintf_s(sNum, "%d", i + 1);
		str += sNum;

		LabelTTF* label = LabelTTF::create(str, "Arial", 40);
		TestLabelList.push_back(label);
	}

	for (int i = 0; i < TEST_STAGE_NUM; ++i)
	{
		LabelTTF* label = TestLabelList[i];
		MenuItemLabel* menuLabel;

		menuLabel = MenuItemLabel::create(label, CC_CALLBACK_0(MySceneStageSelect::TouchStageItem, this));
		menuLabel->setPosition(0.0f, i * -TEST_STAGE_OFFSET);

		MenuItemStageList.push_back(menuLabel);
	}

	Menu = Menu::create(MenuItemStageList[0], MenuItemStageList[1], MenuItemStageList[2], nullptr);
	Menu->setPosition(Vec2(size.width * 0.5f, size.height * 0.8f));
	this->addChild(Menu);

	this->scheduleUpdate();

	return true;
}

void MySceneStageSelect::update(float dt)
{
}

void MySceneStageSelect::InitLabel()
{
}

void MySceneStageSelect::TouchStageItem()
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, HelloWorld::createScene()));
}

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
