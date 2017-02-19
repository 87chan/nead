#include "MySceneStageSelect.h"
#include "HelloWorldScene.h"
#include "GlobalInfo.h"
#include "platform/CCFileUtils.h"
#include "ui/UIWidget.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

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

	// �t�H���_����X�e�[�W��ǂݍ���.
	int searchedStageNum = 1;
	bool bContinue = true;
	std::string fileName = "";

	while (bContinue)
	{
		char sNum[32];
		sprintf_s(sNum, "stage/stage%02d.tmx", searchedStageNum);
		fileName = sNum;
		auto filePath = FileUtils::getInstance()->fullPathForFilename(fileName);

		if (filePath == "")
		{
			--searchedStageNum;
			bContinue = false;
			continue;
		}
		else
		{
			++searchedStageNum;
		}
	}

	// ���x���̍쐬.
	float fontSize = 40.0f;
	float fontOffset = 10.0f;
	float fontSizeIncOffset = fontSize + fontOffset;
	Size ListSize = Size(size.width, (fontSize + fontOffset) * searchedStageNum);
	std::vector<cocos2d::LabelTTF*> testLabelList;
	for (int i = 0; i < searchedStageNum; ++i)
	{
		std::string str = "Stage";
		char sNum[32];
		sprintf_s(sNum, "%d", i + 1);
		str += sNum;

		LabelTTF* label = LabelTTF::create(str, "Arial", fontSize);
		testLabelList.push_back(label);
	}

	// �X�N���[���̐ݒ�.
	auto _scrollView = ui::ScrollView::create();
	_scrollView->setPosition(Vec2(0.0f, 0.0f));
	_scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	_scrollView->setBounceEnabled(false);
	this->addChild(_scrollView);

	//���ۂɕ\�������̈�i����ȊO�͉B���)
	auto inveSize = Size(this->getContentSize().width, size.height);
	_scrollView->setContentSize(inveSize);

	//���g�̃T�C�Y���w��
	_scrollView->setInnerContainerSize(Size(this->getContentSize().width, ListSize.height));

	Size firstPositionOffset = Size(0.0f, fontSize * 0.5f);
	for (int i = 0; i < searchedStageNum; ++i)
	{
		LabelTTF* label = testLabelList[i];
		MenuItemLabel* menuLabel = MenuItemLabel::create(label, CC_CALLBACK_1(MySceneStageSelect::TouchStageItem, this));
		menuLabel->setTag(i + 1);

		cocos2d::Menu* menu = Menu::create(menuLabel, nullptr);
		menu->setPosition(Vec2(size.width * 0.5f, (ListSize.height - firstPositionOffset.height) + i * -fontSizeIncOffset));

		//�X�N���[�����钆�g��ǉ��iLayer��Sprite�Ȃǁj
		_scrollView->addChild(menu);
	}

	this->scheduleUpdate();

	return true;
}

void MySceneStageSelect::update(float dt)
{
}

void MySceneStageSelect::InitLabel()
{
}

void MySceneStageSelect::TouchStageItem(Ref* pSender)
{
	if (MenuItem* item = static_cast<MenuItem*>(pSender))
	{
		char sNum[32];
		sprintf_s(sNum, "stage/stage%02d.tmx", item->getTag());
		GlobalInfo::GetInstance()->stagePath = sNum;

		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, HelloWorld::createScene()));
	}
}

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
