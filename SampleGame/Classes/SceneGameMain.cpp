#include "SceneGameMain.h"

USING_NS_CC;

SceneGameMain::SceneGameMain()
: TitleLabel(nullptr)
{
}

SceneGameMain::~SceneGameMain()
{
}

void SceneGameMain::Initialize()
{
	Size size = Director::getInstance()->getWinSize();

	TitleLabel = cocos2d::LabelTTF::create("Test", "Arial", 40);
	TitleLabel->setPosition(size.width * 0.5f, size.height * 0.6f);
	TitleLabel->setVisible(true);
	this->addChild(TitleLabel);
}

void SceneGameMain::update(float delta)
{
}

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
